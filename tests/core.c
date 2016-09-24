#include "../risky/core.h"
#include "../unit_test_harness/harness.h"
#ifdef __cplusplus
extern "C"{
#endif
test_result_t test_init_risky_vm_state() {
    test_result_t test = TEST;
    test.result = TEST_SUCCESS;
    risky_vm_state_t state = {{0}, NULL};
    init_risky_vm_state(&state);
    if(
        (
            sizeof(state.registers) / sizeof(risky_register_t)
        ) != RISKY_REGISTER_COUNT
    ) {
        test.result = TEST_FAIL;
    }
    for(size_t i = 0; i < RISKY_REGISTER_COUNT; i++) {
        if(state.registers[i] != 0) {
            test.result = TEST_FAIL;
            break;
        }
    }
    if(state.ram == NULL) {
        test.result = TEST_FAIL;
        return test;
    }
    for(size_t i = 0; i < RISKY_RAM_AMOUNT; i++) {
        if(state.ram[i] != 0) {
            test.result = TEST_FAIL;
            break;
        }
    }
    return test;
}
int main() {
    test_suite_t suite = init_test_suite();
    add_test_case(test_init_risky_vm_state, &suite);
    run_test_suite(&suite);
    return suite.result ? 0 : 1;
}
#ifdef __cplusplus
}
#endif
