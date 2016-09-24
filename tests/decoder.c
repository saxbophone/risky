#include <stdbool.h>
#include "../risky/core.h"
#include "../risky/decoder.h"
#include "../risky/risky.h"
#include "../unit_test_harness/harness.h"
#ifdef __cplusplus
extern "C"{
#endif
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
static test_status_t test_decode_no_operands(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    test_status_t test = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { raw_opcode, 0x7fU, 0x33U, 0x69U, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = false, .b_flag = false, .c_flag = false,
        .r = 0, .a = 0, .b = 0,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}
test_result_t test_decode_nop() {
    test_result_t test = TEST;
    test.result = test_decode_no_operands(0x07U, NOP);
    return test;
}
test_result_t test_decode_hlt() {
    test_result_t test = TEST;
    test.result = test_decode_no_operands(0x1fU, HLT);
    return test;
}
test_result_t test_decode_jmp() {
    test_result_t test = TEST;
    test.result = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { 0x0fU, 0xffU, 0x15U, 0x93U, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = JMP,
        .a_flag = false, .b_flag = false, .c_flag = false,
        .r = 0xffU, .a = 0, .b = 0,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test.result = TEST_FAIL;
    }
    return test;
}
test_result_t test_decode_bra() {
    test_result_t test = TEST;
    test.result = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { 0x17U, 0xdbU, 0x9fU, 0x13U, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = BRA,
        .a_flag = true, .b_flag = false, .c_flag = false,
        .r = 0xdbU, .a = 0x9fU, .b = 0,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test.result = TEST_FAIL;
    }
    return test;
}
static test_status_t test_decode_all_operands(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    test_status_t test = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { raw_opcode | 0x07, 0xcaU, 0xfeU, 0x2dU, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = true, .b_flag = true, .c_flag = true,
        .r = 0xcaU, .a = 0xfeU, .b = 0x2dU,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}
test_result_t test_decode_equ() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x04U << 3, EQU);
    return test;
}
test_result_t test_decode_neq() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x05U << 3, NEQ);
    return test;
}
test_result_t test_decode_gtn() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x06U << 3, GTN);
    return test;
}
test_result_t test_decode_ltn() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x07U << 3, LTN);
    return test;
}
test_result_t test_decode_add() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x08U << 3, ADD);
    return test;
}
test_result_t test_decode_sub() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x09U << 3, SUB);
    return test;
}
test_result_t test_decode_mlt() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x0aU << 3, MLT);
    return test;
}
test_result_t test_decode_div() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x0bU << 3, DIV);
    return test;
}
test_result_t test_decode_mod() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x0cU << 3, MOD);
    return test;
}
test_result_t test_decode_eor() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x10U << 3, EOR);
    return test;
}
test_result_t test_decode_and() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x11U << 3, AND);
    return test;
}
test_result_t test_decode_xor() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x12U << 3, XOR);
    return test;
}
test_result_t test_decode_lsh() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x14U << 3, LSH);
    return test;
}
test_result_t test_decode_rsh() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x15U << 3, RSH);
    return test;
}
test_result_t test_decode_cas() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x17U << 3, CAS);
    return test;
}
test_result_t test_decode_qdc() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x1cU << 3, QDC);
    return test;
}
test_result_t test_decode_cdc() {
    test_result_t test = TEST;
    test.result = test_decode_all_operands(0x1dU << 3, CDC);
    return test;
}
static test_status_t test_decode_two_register_operands(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    test_status_t test = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { raw_opcode | 0x06, 0xcaU, 0xfeU, 0x2dU, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = true, .b_flag = true, .c_flag = false,
        .r = 0xcaU, .a = 0xfeU, .b = 0,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}
test_result_t test_decode_inc() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x0dU << 3, INC);
    return test;
}
test_result_t test_decode_dec() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x0eU << 3, DEC);
    return test;
}
test_result_t test_decode_not() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x13U << 3, NOT);
    return test;
}
test_result_t test_decode_rot() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x16U << 3, ROT);
    return test;
}
test_result_t test_decode_cop() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x19U << 3, COP);
    return test;
}
test_result_t test_decode_lod() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x1aU << 3, LOD);
    return test;
}
test_result_t test_decode_sav() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands(0x1bU << 3, SAV);
    return test;
}
test_result_t test_decode_qop() {
    test_result_t test = TEST;
    test.result = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { 0x7fU, 0xffU, 0x15U, 0x93U, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = QOP,
        .a_flag = true, .b_flag = true, .c_flag = true,
        .r = 0xffU, .a = 0, .b = 0,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test.result = TEST_FAIL;
    }
    return test;
}
test_result_t test_decode_set() {
    test_result_t test = TEST;
    test.result = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { 0xc4U, 0xf9U, 0xd7U, 0x32U, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = SET,
        .a_flag = true, .b_flag = false, .c_flag = false,
        .r = 0xf9U, .a = 0, .b = 0,
        .l = 0xd732U,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test.result = TEST_FAIL;
    }
    return test;
}
static test_status_t test_decode_two_register_operands_no_flags(
    risky_byte_t raw_opcode, risky_opcode_t opcode
) {
    test_status_t test = TEST_SUCCESS;
    risky_raw_instruction_t raw = {
        .bytes = { raw_opcode, 0xcaU, 0xfeU, 0x2dU, },
    };
    risky_instruction_t output;
    risky_instruction_t expected = {
        .opcode = opcode,
        .a_flag = false, .b_flag = false, .c_flag = false,
        .r = 0xcaU, .a = 0xfeU, .b = 0,
        .l = 0,
    };
    status_t result = decode_instruction_from_raw(&raw, &output);
    if(result != STATUS_SUCCESS) {
        test = TEST_ERROR;
        return test;
    }
    if(!instructions_equal(output, expected)) {
        test = TEST_FAIL;
    }
    return test;
}
test_result_t test_decode_rea() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands_no_flags(0x1eU << 3, REA);
    return test;
}
test_result_t test_decode_wri() {
    test_result_t test = TEST;
    test.result = test_decode_two_register_operands_no_flags(0x1fU << 3, WRI);
    return test;
}
int main() {
    test_suite_t suite = init_test_suite();
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
    add_test_case(test_decode_qdc, &suite);
    add_test_case(test_decode_cdc, &suite);
    add_test_case(test_decode_inc, &suite);
    add_test_case(test_decode_dec, &suite);
    add_test_case(test_decode_not, &suite);
    add_test_case(test_decode_rot, &suite);
    add_test_case(test_decode_cop, &suite);
    add_test_case(test_decode_lod, &suite);
    add_test_case(test_decode_sav, &suite);
    add_test_case(test_decode_qop, &suite);
    add_test_case(test_decode_set, &suite);
    add_test_case(test_decode_rea, &suite);
    add_test_case(test_decode_wri, &suite);
    run_test_suite(&suite);
    return suite.result ? 0 : 1;
}
#ifdef __cplusplus
}
#endif
