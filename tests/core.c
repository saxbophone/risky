// unit tests for the core module
#include "../risky/core.h"
#include "../unit_test_harness/harness.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * Function init_risky_vm_state should populate the struct at a given pointer
 * with default values, and allocate memory for it.
 */
test_result_t test_init_risky_vm_state() {
    // initialise test result
    test_result_t test = TEST;
    // set result to success for now, until proven otherwise by checks
    test.result = TEST_SUCCESS;

    // create risky_vm_state_t struct with all fields set to 0
    risky_vm_state_t state = {{0}, NULL};

    // call function with address of state
    init_risky_vm_state(&state);

    // check size of registers array is correct
    if(
        (
            sizeof(state.registers) / sizeof(risky_register_t)
        ) != RISKY_REGISTER_COUNT
    ) {
        test.result = TEST_FAIL;
    }
    // check all registers are set to 0
    for(size_t i = 0; i < RISKY_REGISTER_COUNT; i++) {
        if(state.registers[i] != 0) {
            test.result = TEST_FAIL;
            break;
        }
    }
    // check ram pointer is not NULL (memory has been allocated)
    if(state.ram == NULL) {
        test.result = TEST_FAIL;
    }
    // check all RAM is set to 0 (good indicator if enough has been allocated)
    for(size_t i = 0; i < RISKY_RAM_AMOUNT; i++) {
        if(state.ram[i] != 0) {
            test.result = TEST_FAIL;
            break;
        }
    }
    return test;
}

int main() {
    // initialise test suite
    test_suite_t suite = init_test_suite();
    // add test cases
    add_test_case(test_init_risky_vm_state, &suite);
    // run test suite
    run_test_suite(&suite);
    // return test suite status
    return suite.result ? 0 : 1;
}

#ifdef __cplusplus
} // extern "C"
#endif
