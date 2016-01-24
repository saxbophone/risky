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
    instruction.data.opcode = SUB;
    instruction.data.rds_register = 0x2;
    instruction.data.operands.registers.a = 0x1;
    instruction.data.operands.registers.b = 0x7;
    printf("Instruction size is %lu bytes\n", sizeof(instruction));
    printf("Instruction operands make up %lu byte\n", sizeof(instruction.data.operands));
    printf("Full instruction in raw format: 0x%02X%02X\n", instruction.raw[0], instruction.raw[1]);
    return 0;
}
