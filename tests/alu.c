/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Joshua Saxby joshua.a.saxby+TNOPLuc8vM==@gmail.com
 *
 * this compilation unit contains unit tests for the alu module
 */
#include "../unit_test_harness/harness.h"


#ifdef __cplusplus
extern "C"{
#endif

// a dummy test case
test_result_t test_nothing() {
    // initialise test result
    test_result_t test = TEST;
    return test;
}

int main() {
    // initialise test suite
    test_suite_t suite = init_test_suite();
    // add test cases
    add_test_case(test_nothing, &suite);
    // run test suite
    run_test_suite(&suite);
    // return test suite status
    return suite.result ? 0 : 1;
}

#ifdef __cplusplus
} // extern "C"
#endif
