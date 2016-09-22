/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Joshua Saxby joshua.a.saxby+TNOPLuc8vM==@gmail.com
 *
 * decoder - this compilation unit defines functions used for decoding binary
 * data into the instructions they represent
 */
#ifndef SAXBOPHONE_RISKY_DECODER_H
#define SAXBOPHONE_RISKY_DECODER_H

#include "core.h"
#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * given a pointer to a risky_raw_instruction_t and a pointer to a
 * risky_instruction_t, decode the raw instruction data and write the
 * instruction opcode, flags and operands to the risky_instruction_t.
 * returns a status_t with error / success information
 */
status_t decode_instruction_from_raw(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction
);

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
