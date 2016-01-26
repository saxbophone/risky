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
#include <unistd.h>

#include "risky.h"

int main(int argc, char const *argv[]) {
    /*
     * This example code initialises a RISKY state struct from a file containing
     * binary code that represents RISKY instructions.
     */
    risky_state_t state = risky_init();
    if(risky_boot("example_file.bin", &state)) {
        risky_dump(&state);
        while(true) {
            risky_run(&state);
            risky_dump(&state);
            usleep(50000);
        }
        return 0;
    } else {
        fprintf(stderr, "Couldn't boot from file.\n");
        return 1;
    }
}
