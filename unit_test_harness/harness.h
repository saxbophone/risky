/*
 * harness - this compilation unit provides a simple test harness to use for the
 * unit tests of RISKY
 */
#ifndef SAXBOPHONE_RISKY_TEST_HARNESS_H
#define SAXBOPHONE_RISKY_TEST_HARNESS_H

#include <stdbool.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C"{
#endif

// enum for test suite test case results
typedef enum test_status_t {
    TEST_UNKNOWN = 0,
    TEST_FAIL,
    TEST_ERROR,
    TEST_SUCCESS,
} test_status_t;

// struct for test result and test name
typedef struct test_result_t {
    test_status_t result;
    const char * name;
} test_result_t;

/*
 * macro for storing function name as test name
 * usage: test_result_t result = TEST;
 */
#define TEST (test_result_t) { .result = TEST_UNKNOWN, .name = __func__, }

// struct for representing a test case
typedef struct test_case_t {
    // function pointer to function to run for test
    test_result_t (* function)();
    // test result status
    test_result_t result;
} test_case_t;

// struct for representing a whole test suite (one per module/test executable)
typedef struct test_suite_t {
    // pointer to an array of test cases
    test_case_t * tests;
    size_t test_count;
    // test suite fail / pass flag
    bool result;
} test_suite_t;

// returns a blank test suite
test_suite_t init_test_suite();

/*
 * adds a function as a test case to a test suite
 * function must return a test_result_t struct and take no arguments
 */
void add_test_case(test_result_t (* function)(), test_suite_t * suite);

// runs all test cases in a test suite and stores result success / failure
void run_test_suite(test_suite_t * suite);

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
