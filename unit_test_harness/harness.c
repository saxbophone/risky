#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "harness.h"
#ifdef __cplusplus
extern "C"{
#endif
test_suite_t init_test_suite() {
    return (test_suite_t) { .tests = NULL, .test_count = 0, .result = true };
}
void add_test_case(test_result_t (* function)(), test_suite_t * suite) {
    suite->test_count++;
    if(suite->tests == NULL) {
        suite->tests = (test_case_t *) malloc(sizeof(test_case_t));
    } else {
        suite->tests = (test_case_t *) realloc(
            suite->tests, sizeof(test_case_t) * suite->test_count
        );
    }
    suite->tests[suite->test_count - 1].function = function;
}
static const char * test_status_string(test_status_t status) {
    switch(status) {
        case TEST_UNKNOWN:
            return "NO RESULT";
        case TEST_FAIL:
            return "FAIL";
        case TEST_ERROR:
            return "ERROR";
        case TEST_SUCCESS:
            return "SUCCESS";
        default:
            return "UNEXPECTED RESULT";
    }
}
void run_test_suite(test_suite_t * suite) {
    for(size_t i = 0; i < suite->test_count; i++) {
        test_result_t result = suite->tests[i].function();
        printf("%s\t%s\n", result.name, test_status_string(result.result));
        suite->result = (
            (result.result == TEST_SUCCESS) ? true : false
        ) && suite->result;
    }
}
#ifdef __cplusplus
}
#endif
