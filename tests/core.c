/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Joshua Saxby joshua.a.saxby+TNOPLuc8vM==@gmail.com
 *
 * this compilation unit contains unit tests for the core module
 */
#include "../risky/core.h"
#include "../risky/risky.h"
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

    // call function with address of state and store result
    status_t result = init_risky_vm_state(&state);

    // check if function status was success
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    // check size of registers array is correct
    if(
        (
            sizeof(state.registers) / sizeof(risky_register_t)
        ) != RISKY_REGISTER_COUNT
    ) {
        test.result = TEST_FAIL;
        return test;
    }
    // check all registers are set to 0
    for(size_t i = 0; i < RISKY_REGISTER_COUNT; i++) {
        if(state.registers[i] != 0) {
            test.result = TEST_FAIL;
            return test;
        }
    }
    // check ram pointer is not NULL (memory has been allocated)
    if(state.ram == NULL) {
        test.result = TEST_FAIL;
        return test;
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

/*
 * Function free_risky_vm_state should clear the fields of a struct at a given
 * pointer and free memory previously allocated for it.
 */
test_result_t test_free_risky_vm_state() {
    // initialise test result
    test_result_t test = TEST;
    // set result to success for now, until proven otherwise by checks
    test.result = TEST_SUCCESS;

    // create risky_vm_state_t struct with all fields set to 0
    risky_vm_state_t state = {{0}, NULL};
    // allocate memory for struct
    init_risky_vm_state(&state);
    // write some values to RAM and registers
    state.registers[36] = 0x3bdfU;
    state.registers[178] = 0x9c15U;
    state.ram[12345] = 0x9fU;
    state.ram[65535] = 0xdaU;
    state.ram[32767] = 0x31U;

    // call function with state and store result
    status_t result = free_risky_vm_state(&state);

    // check if function status was success
    if(result != STATUS_SUCCESS) {
        test.result = TEST_ERROR;
        return test;
    }
    // check all registers are set to 0
    for(size_t i = 0; i < RISKY_REGISTER_COUNT; i++) {
        if(state.registers[i] != 0) {
            test.result = TEST_FAIL;
            return test;
        }
    }
    // check ram pointer is NULL (no memory allocated)
    if(state.ram != NULL) {
        test.result = TEST_FAIL;
        return test;
    }
    return test;
}

int main() {
    // initialise test suite
    test_suite_t suite = init_test_suite();
    // add test cases
    add_test_case(test_init_risky_vm_state, &suite);
    add_test_case(test_free_risky_vm_state, &suite);
    // run test suite
    run_test_suite(&suite);
    // return test suite status
    return suite.result ? 0 : 1;
}

#ifdef __cplusplus
} // extern "C"
#endif
