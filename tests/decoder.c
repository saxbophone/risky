// unit tests for the decoder module
#include <stdbool.h>

#include "../risky/core.h"
#include "../risky/decoder.h"
#include "../risky/risky.h"
#include "../unit_test_harness/harness.h"


#ifdef __cplusplus
extern "C"{
#endif

// test helper function for testing if two risky_instruction_t objects are equal
static bool instructions_equal(risky_instruction_t a, risky_instruction_t b) {
    return (
        (a.opcode != b.opcode) ||
        (a.a_flag != b.a_flag) ||
        (a.b_flag != b.b_flag) ||
        (a.c_flag != b.c_flag) ||
        (a.r != b.r) ||
        (a.a != b.a) ||
        (a.b != b.b) ||
        (a.l != b.l)
    ) ? false : true;
}

/*
 * test helper function for testing opcodes / instructions that should ignore
 * any operands or flags that are also passed to them
 */
static test_status_t test_decode_no_operands(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    // initialise test status to success for now, until proven otherwise
    test_status_t test = TEST_SUCCESS;

    // setup input raw instruction
    risky_raw_instruction_t raw = {
        /*
         * set first byte to the value of raw_opcode
         * set remaining three bytes to anything but complete 0 to prove
         * operands are being ignored
         */
        .bytes = { raw_opcode, 0x7fU, 0x33U, 0x69U, },
    };
    // setup blank output instruction
    risky_instruction_t output;
    // setup expected output instruction
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = false, .b_flag = false, .c_flag = false,
        .r = 0, .a = 0, .b = 0,
        .l = 0,
    };

    // run decoder function
    status_t result = decode_instruction_from_raw(&raw, &output);

    // if function failed, return error
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    // check if output is equal to expected
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}

/*
 * the NOP (no-op) instruction should decode to the correct opcode
 * no operands or flags should be set (even if the raw data fields that they
 * map to contain non-zero data), because NOP never takes any arguments.
 */
test_result_t test_decode_nop() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_no_operands(0x07U, NOP);

    return test;
}

/*
 * the HLT (halt) instruction should decode to the correct opcode
 * no operands or flags should be set (even if the raw data fields that they
 * map to contain non-zero data), because HLT never takes any arguments.
 */
test_result_t test_decode_hlt() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_no_operands(0x1fU, HLT);

    return test;
}

/*
 * the JMP (jump) instruction should decode to the correct opcode
 * JMP is unique in being the only instruction that takes one memory address
 * as its sole argument. Therefore, all other flags and the first operand should
 * be ignored by the decoder, even if not zero.
 */
test_result_t test_decode_jmp() {
    // initialise test result
    test_result_t test = TEST;

    // setup input raw instruction
    risky_raw_instruction_t raw = {
        /*
         * first byte should be 0b00001111 (0x0f)
         * second byte should be anything but complete 0 to prove operands are
         * being ignored
         * third and fourth bytes should store the memory address, in
         * big-endian format
         */
        .bytes = { 0x0fU, 0xffU, 0x15U, 0x93U, },
    };
    // setup blank output instruction
    risky_instruction_t output;
    // setup expected output instruction
    risky_instruction_t expected = {
        .opcode = JMP,
        .a_flag = false, .b_flag = false, .c_flag = false,
        .r = 0, .a = 0, .b = 0,
        .l = 0x1593U,
    };

    // run decoder function
    status_t result = decode_instruction_from_raw(&raw, &output);

    // if function failed, return error
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    // check if output is equal to expected
    if(!instructions_equal(output, expected)) {
        test.result = TEST_FAIL;
    }
    return test;
}

/*
 * the BRA (branch) instruction should decode to the correct opcode
 * BRA takes three arguments: a flag telling it whether to evaluate the register
 * as an 8-bit value or a 16-bit value, the register to check the value of and
 * a memory address to jump to (if the evaluation of the register is true)
 * the other two flags are ignored, even if non-zero.
 */
test_result_t test_decode_bra() {
    // initialise test result
    test_result_t test = TEST;

    // setup input raw instruction
    risky_raw_instruction_t raw = {
        /*
         * first byte should be 0b00010111 (0x17)
         * second byte is the register address
         * third and fourth bytes should store the memory address, in
         * big-endian format
         */
        .bytes = { 0x17U, 0xdbU, 0x9fU, 0x13U, },
    };
    // setup blank output instruction
    risky_instruction_t output;
    // setup expected output instruction
    risky_instruction_t expected = {
        .opcode = BRA,
        .a_flag = true, .b_flag = false, .c_flag = false,
        .r = 0xdbU, .a = 0, .b = 0,
        .l = 0x9f13U,
    };

    // run decoder function
    status_t result = decode_instruction_from_raw(&raw, &output);

    // if function failed, return error
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    // check if output is equal to expected
    if(!instructions_equal(output, expected)) {
        test.result = TEST_FAIL;
    }
    return test;
}

/*
 * test helper function for testing opcodes / instructions that use all operands
 * (except the memory address which is replaced by the two extra registers)
 * and require these to be read by the instruction decoder
 */
static test_status_t test_decode_all_operands(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    // initialise test status to success for now, until proven otherwise
    test_status_t test = TEST_SUCCESS;

    // setup input raw instruction
    risky_raw_instruction_t raw = {
        /*
         * set first byte to the value of raw_opcode, OR'ed with 3 1 bits at end
         * set remaining three bytes to anything but complete 0 to prove
         * operands are being read
         */
        .bytes = { raw_opcode | 0x07, 0xcaU, 0xfeU, 0x2dU, },
    };
    // setup blank output instruction
    risky_instruction_t output;
    // setup expected output instruction
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = true, .b_flag = true, .c_flag = true,
        .r = 0xcaU, .a = 0xfeU, .b = 0x2dU,
        .l = 0,
    };

    // run decoder function
    status_t result = decode_instruction_from_raw(&raw, &output);

    // if function failed, return error
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    // check if output is equal to expected
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}

/*
 * the EQU (equality check) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_equ() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x04U << 3, EQU);

    return test;
}

/*
 * the NEQ (inequality check) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_neq() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x05U << 3, NEQ);

    return test;
}

/*
 * the GTN (greater-than check) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_gtn() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x06U << 3, GTN);

    return test;
}

/*
 * the LTN (less-than check) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_ltn() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x07U << 3, LTN);

    return test;
}

/*
 * the ADD (addition) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_add() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x08U << 3, ADD);

    return test;
}

/*
 * the SUB (subtraction) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_sub() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x09U << 3, SUB);

    return test;
}

/*
 * the MLT (multiplication) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_mlt() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x0aU << 3, MLT);

    return test;
}

/*
 * the DIV (division) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_div() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x0bU << 3, DIV);

    return test;
}

/*
 * the MOD (modulo division) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_mod() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x0cU << 3, MOD);

    return test;
}

/*
 * the EOR (bitwise or) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_eor() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x10U << 3, EOR);

    return test;
}

/*
 * the AND (bitwise and) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_and() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x11U << 3, AND);

    return test;
}

/*
 * the XOR (bitwise xor) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_xor() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x12U << 3, XOR);

    return test;
}

/*
 * the LSH (left shift) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_lsh() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x14U << 3, LSH);

    return test;
}

/*
 * the RSH (right shift) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_rsh() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x15U << 3, RSH);

    return test;
}

/*
 * the CAS (cascade shift) instruction should decode to the correct opcode
 * all three flags should be read from the raw instruction and all three
 * register addresses
 */
test_result_t test_decode_cas() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_all_operands(0x17U << 3, CAS);

    return test;
}

/*
 * test helper function for testing opcodes / instructions that use two register
 * operands (result register address and one operand address), along with two
 * flags for these. All unused parameters are tested for 0 (should be ignored)
 * TODO: finish this
 */
static test_status_t test_decode_two_register_operands(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    // initialise test status to success for now, until proven otherwise
    test_status_t test = TEST_SUCCESS;

    // setup input raw instruction
    risky_raw_instruction_t raw = {
        /*
         * set first byte to the value of raw_opcode, OR'ed with 2 1 bits at end
         * set remaining three bytes to anything but complete 0 to prove that
         * the first two operands are being read
         */
        .bytes = { raw_opcode | 0x06, 0xcaU, 0xfeU, 0x2dU, },
    };
    // setup blank output instruction
    risky_instruction_t output;
    // setup expected output instruction
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = true, .b_flag = true, .c_flag = false,
        .r = 0xcaU, .a = 0xfeU, .b = 0,
        .l = 0,
    };

    // run decoder function
    status_t result = decode_instruction_from_raw(&raw, &output);

    // if function failed, return error
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    // check if output is equal to expected
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}

/*
 * the INC (increment) instruction should decode to the correct opcode
 * two flags should be read from the raw instruction and two register addresses
 */
test_result_t test_decode_inc() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_two_register_operands(0x0dU << 3, INC);

    return test;
}

/*
 * the DEC (decrement) instruction should decode to the correct opcode
 * two flags should be read from the raw instruction and two register addresses
 */
test_result_t test_decode_dec() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_two_register_operands(0x0eU << 3, DEC);

    return test;
}

/*
 * the NOT (bitwise not) instruction should decode to the correct opcode
 * two flags should be read from the raw instruction and two register addresses
 */
test_result_t test_decode_not() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_two_register_operands(0x13U << 3, NOT);

    return test;
}

/*
 * the ROT (rotate bits) instruction should decode to the correct opcode
 * two flags should be read from the raw instruction and two register addresses
 */
test_result_t test_decode_rot() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_two_register_operands(0x16U << 3, ROT);

    return test;
}

/*
 * the COP (copy register) instruction should decode to the correct opcode
 * two flags should be read from the raw instruction and two register addresses
 */
test_result_t test_decode_cop() {
    // initialise test result
    test_result_t test = TEST;

    // set result to return result of helper functuion
    test.result = test_decode_two_register_operands(0x19U << 3, COP);

    return test;
}

int main() {
    // initialise test suite
    test_suite_t suite = init_test_suite();
    // add test cases
    add_test_case(test_decode_nop, &suite);
    add_test_case(test_decode_hlt, &suite);
    add_test_case(test_decode_jmp, &suite);
    add_test_case(test_decode_bra, &suite);
    add_test_case(test_decode_equ, &suite);
    add_test_case(test_decode_neq, &suite);
    add_test_case(test_decode_gtn, &suite);
    add_test_case(test_decode_ltn, &suite);
    add_test_case(test_decode_add, &suite);
    add_test_case(test_decode_sub, &suite);
    add_test_case(test_decode_mlt, &suite);
    add_test_case(test_decode_div, &suite);
    add_test_case(test_decode_mod, &suite);
    add_test_case(test_decode_eor, &suite);
    add_test_case(test_decode_and, &suite);
    add_test_case(test_decode_xor, &suite);
    add_test_case(test_decode_lsh, &suite);
    add_test_case(test_decode_rsh, &suite);
    add_test_case(test_decode_cas, &suite);
    add_test_case(test_decode_inc, &suite);
    add_test_case(test_decode_dec, &suite);
    add_test_case(test_decode_not, &suite);
    add_test_case(test_decode_rot, &suite);
    add_test_case(test_decode_cop, &suite);
    // run test suite
    run_test_suite(&suite);
    // return test suite status
    return suite.result ? 0 : 1;
}

#ifdef __cplusplus
} // extern "C"
#endif
