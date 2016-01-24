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

    // Populates a byte array with the raw bytes that represent an instruction struct
    void instruction_to_raw(instruction_t instruction, instruction_raw_t * raw_instruction) {
        // The instruction is processed 4 bits at a time, as that's the lowest value we care about.
        // This makes sure machine-specific endianness doesn't cause any problems.
        raw_instruction[0] += (instruction.opcode << 4); // bit mask the higher 4 bits
        raw_instruction[0] += instruction.primary; // no bitmask needed, lower 4 bits
        raw_instruction[1] += (instruction.operands.registers.a << 4); // bit mask the higher 4 bits
        raw_instruction[1] += (instruction.operands.registers.b); // no bitmask needed, lower 4 bits
    }

    // Creates and returns a new instruction struct from raw bytes
    instruction_t instruction_from_raw(instruction_raw_t * raw_instruction) {
        // The instruction is processed 4 bits at a time, as that's the lowest value we care about.
        // This makes sure machine-specific endianness doesn't cause any problems.
        instruction_t instruction;
        instruction.opcode = (raw_instruction[0] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.primary = (raw_instruction[0] & 0x0FU); // bit mask the lower 4 bits
        instruction.operands.registers.a = (raw_instruction[1] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.operands.registers.b = (raw_instruction[1] & 0x0FU); // bit mask the lower 4 bits
        return instruction;
    }

#ifdef __cplusplus
} // extern "C"
#endif
