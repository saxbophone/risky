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
    instruction_struct_t instruction;
    printf("%lu\n", sizeof(instruction));
    return 0;
}
