/*
 * RISKY
 *
 * A tiny virtual processor with a RISC-inspired instruction set
 *
 * Copyright (c) 2016 Joshua Saxby
 *
 * See README.md for more information and LICENSE for licensing details.
 *
 * This program will attempt to load and run a binary file containing machine
 * bitcode, the file path of which should be passed as the sole argument.
 */

#include <stdio.h>

#include "risky.h"

int main(int argc, char const *argv[]) {
    // check if argument count is 2
    if(argc == 2) {
        // assume sole parameter is filepath and attempt to boot from it
        risky_state_t state = risky_init();
        if(risky_boot((char *)argv[1], &state)) {
            // if boot was successful, run CPU loop until risky_run returns false
            while(risky_run(&state)) {
                dump_registers(&state);
            }
            return 0;
        } else {
            fprintf(stderr, "Couldn't boot from file.\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Too many or few arguments given.\n");
        fprintf(stderr, "Please specify filepath of executable code as sole command-line argument.\n");
        return 1;
    }
}
