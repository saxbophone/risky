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

    // create uninitialised risky_vm_state_t struct
    risky_vm_state_t state;

    // call function with address of state
    init_risky_vm_state(&state);

    // check state struct
    // TODO ^^^
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
