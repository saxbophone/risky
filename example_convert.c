/*
 * RISKY
 *
 * A tiny virtual processor with a RISC-inspired instruction set
 *
 * Copyright (c) 2016 Joshua Saxby
 *
 * See README.md for more information and LICENSE for licensing details.
 */

#include <stdio.h>

#include "risky.h"

int main(int argc, char const *argv[])
{
    /*
     * This example code builds a RISKY instruction from raw bytes.
     */
    instruction_raw_t raw_instruction[2] = { 0x03, 0x12 }; // ADD reg1 to reg2, store in reg 3
    printf("%02X%02X\n", raw_instruction[0], raw_instruction[1]);
    instruction_t instruction = instruction_from_raw(raw_instruction);
    printf(
        "Full instruction in raw format: 0x%01X%01X%01X%01X\n",
        instruction.opcode, instruction.primary,
        instruction.operands.registers.a, instruction.operands.registers.b
    );
    instruction_raw_t raw[2] = { 0x00, 0x00 };
    instruction_to_raw(instruction, raw);
    printf("%02X%02X\n", raw[0], raw[1]);
    return 0;
}
