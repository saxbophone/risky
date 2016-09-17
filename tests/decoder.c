// unit tests for the decoder module
#include "../risky/core.h"
#include "../risky/decoder.h"
#include "../risky/risky.h"
#include "../unit_test_harness/harness.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * the NOP (no-op) instruction should decode to the correct opcode
 * no operands or flags should be set (even if the raw data fields that they
 * map to contain non-zero data), because NOP never takes any arguments.
 */
test_result_t test_decode_nop() {
    // initialise test result
    test_result_t test = TEST;
    // set result to success for now, until proven otherwise by checks
    test.result = TEST_SUCCESS;

    // setup input raw instruction
    risky_raw_instruction_t raw = {
        /*
         * set first 5 bits of first byte to 0, last 3 bits to 1
         * set remaining three bytes to anything but complete 0 to prove
         * operands are being ignored
         */
        .bytes = { 0x07U, 0x7fU, 0x33U, 0x69U, },
    };
    // setup blank output instruction
    risky_instruction_t output;
    // setup expected output instruction
    risky_instruction_t expected = {
        .opcode = NOP,
        .a_flag = false, .b_flag = false, .c_flag = false,
        .r = 0, .a = 0, .b = 0,
        .l = 0,
    };

    // run decoder function
    status_t result = decode_instruction_from_raw(&raw, &output);

    // if function failed, return error
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    // check all fields against output
    if(
        (output.opcode != expected.opcode) ||
        (output.a_flag != expected.a_flag) ||
        (output.b_flag != expected.b_flag) ||
        (output.c_flag != expected.c_flag) ||
        (output.r != expected.r) ||
        (output.a != expected.a) ||
        (output.b != expected.b) ||
        (output.l != expected.l)
    ) {
        test.result = TEST_FAIL;
    }
    return test;
}

int main() {
    // initialise test suite
    test_suite_t suite = init_test_suite();
    // add test cases
    add_test_case(test_decode_nop, &suite);
    // run test suite
    run_test_suite(&suite);
    // return test suite status
    return suite.result ? 0 : 1;
}

#ifdef __cplusplus
} // extern "C"
#endif
