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
    instruction_t instruction;
    instruction.opcode = GRT;
    instruction.rds_register = 0x2;
    instruction.operands.registers.a = 0x1;
    instruction.operands.registers.b = 0x7;
    printf("Instruction size is %lu bytes\n", sizeof(instruction));
    printf("Instruction operands make up %lu byte\n", sizeof(instruction.operands));
    printf(
        "Full instruction in raw format: 0x%01X%01X%01X%01X\n",
        instruction.opcode, instruction.rds_register, instruction.operands.registers.a, instruction.operands.registers.b);
    return 0;
}
