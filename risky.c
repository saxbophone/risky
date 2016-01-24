/*
 * RISKY
 *
 * A tiny virtual processor with a RISC-inspired instruction set
 *
 * Copyright (c) 2016 Joshua Saxby
 *
 * See README.md for more information and LICENSE for licensing details.
 */

#include "risky.h"

#ifdef __cplusplus
extern "C"{
#endif

    // Returns the raw bytes of an instruction struct
    instruction_raw_t * instruction_to_raw(instruction_t instruction) {
        instruction_raw_t raw_instruction;
    }
    // Creates a new instruction struct from raw bytes
    instruction_t instruction_from_raw(instruction_raw_t raw_instruction) {
        instruction_t instruction;
    }

#ifdef __cplusplus
} // extern "C"
#endif
