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
    instruction_raw_t raw_instruction = { 0x03, 0x12 }; // ADD reg1 to reg2, store in reg 3
    instruction_t instruction = instruction_from_raw(raw_instruction);
    printf(
        "Full instruction in raw format: 0x%01X%01X%01X%01X\n",
        instruction.opcode, instruction.primary,
        instruction.operands.registers.a, instruction.operands.registers.b
    );
    return 0;
}
