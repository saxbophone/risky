#ifndef SAXBOPHONE_RISKY_TEST_HARNESS_H
#include <stdbool.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C"{
#endif
typedef enum test_status_t {
    TEST_UNKNOWN = 0,
    TEST_FAIL,
    TEST_ERROR,
    TEST_SUCCESS,
} test_status_t;
typedef struct test_result_t {
    test_status_t result;
    const char * name;
} test_result_t;
typedef struct test_case_t {
    test_result_t (* function)();
    test_result_t result;
} test_case_t;
typedef struct test_suite_t {
    test_case_t * tests;
    size_t test_count;
    bool result;
} test_suite_t;
test_suite_t init_test_suite();
void add_test_case(test_result_t (* function)(), test_suite_t * suite);
void run_test_suite(test_suite_t * suite);
#ifdef __cplusplus
}
#endif
#endif
