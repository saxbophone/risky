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
#include <time.h>

#include "risky.h"

int main(int argc, char const *argv[])
{
    /*
     * This example code initialises a RISKY state struct and runs some
     * instructions on it, dumping machine state after each instruction.
     */
    risky_state_t state = risky_init();
    risky_dump(&state);
    while(1) {
        risky_run(&state);
        risky_dump(&state);
        unsigned int wait = time(0) + 1;
        while(time(0) < wait);
    }
    return 0;
}
