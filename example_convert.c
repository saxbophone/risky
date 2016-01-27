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

int main(int argc, char const *argv[]) {
    /*
     * This example code demonstrates util code I wrote for converting big-endian
     * array to 16 bit int works.
     */
    uint16_t cage = 34172;
    printf("%04X\n", cage);
    uint8_t cages[2] = {};
    short_to_bytes(cage, cages);
    printf("%02X, %02X\n", cages[0], cages[1]);
    uint16_t open = bytes_to_short(cages);
    printf("%04X\n", open);
    return 0;
}
