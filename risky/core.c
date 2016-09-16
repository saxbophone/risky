/*
 * core - this compilation unit defines the data types used for representing the
 * state of the RISKY virtual machine, and some functions for creating and
 * destroying objects of such types.
 */
#include "core.h"
#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * given a pointer to a risky_vm_state_t, initialises the state struct,
 * allocates memory, etc...
 * Returns a status_t with error / success information
 */
status_t init_risky_vm_state(risky_vm_state_t * state) {
    state->nothing = 73;
    status_t result = STATUS_SUCCESS;
    return result;
}

#ifdef __cplusplus
} // extern "C"
#endif
