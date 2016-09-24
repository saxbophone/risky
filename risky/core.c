/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Joshua Saxby joshua.a.saxby+TNOPLuc8vM==@gmail.com
 *
 * core - this compilation unit defines the data types used for representing the
 * state of the RISKY virtual machine, and some functions for creating and
 * destroying objects of such types.
 */
#include <stdlib.h>

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
    status_t result = STATUS_SUCCESS;
    // allocate memory for RAM, set all to zero
    state->ram = (risky_ram_t *) calloc(RISKY_RAM_AMOUNT, sizeof(risky_ram_t));
    // check if allocation was denied and return MALLOC_REFUSED error code
    if(state->ram == NULL) {
        result = MALLOC_REFUSED;
    }
    return result;
}

/*
 * given a pointer to a risky_vm_state_t, de-initialises the state struct,
 * frees memory, etc...
 * Returns a status_t with error / success information
 */
status_t free_risky_vm_state(risky_vm_state_t * state) {
    status_t result = STATUS_SUCCESS;
    // set all registers to 0
    for(size_t i = 0; i < RISKY_REGISTER_COUNT; i++) {
        state->registers[i] = 0x00U;
    }
    // de-allocate memory if pointer is not NULL
    if(state->ram != NULL) {
        free(state->ram);
        state->ram = NULL;
    }
    return result;
}

#ifdef __cplusplus
} // extern "C"
#endif
