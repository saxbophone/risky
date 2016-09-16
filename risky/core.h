/*
 * core - this compilation unit defines the data types used for representing the
 * state of the RISKY virtual machine, and some functions for creating and
 * destroying objects of such types.
 */
#ifndef SAXBOPHONE_RISKY_CORE_H
#define SAXBOPHONE_RISKY_CORE_H

#include <stdint.h>

#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

// risky vm state struct
typedef struct risky_vm_state_t {
    uint8_t nothing; // TODO: Replace with something more meaningful
} risky_vm_state_t;

/*
 * given a pointer to a risky_vm_state_t, initialises the state struct,
 * allocates memory, etc...
 * Returns a status_t with error / success information
 */
status_t init_risky_vm_state(risky_vm_state_t * state);

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
