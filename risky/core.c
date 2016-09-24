#include <stdlib.h>
#include "core.h"
#include "risky.h"
#ifdef __cplusplus
extern "C"{
#endif
status_t init_risky_vm_state(risky_vm_state_t * state) {
    status_t result = STATUS_SUCCESS;
    state->ram = (risky_ram_t *) calloc(RISKY_RAM_AMOUNT, sizeof(risky_ram_t));
    if(state->ram == NULL) {
        result = MALLOC_REFUSED;
    }
    return result;
}
#ifdef __cplusplus
}
#endif
