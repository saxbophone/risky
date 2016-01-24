/*
 * RISKY
 *
 * A tiny virtual processor with a RISC-inspired instruction set
 *
 * Copyright (c) 2016 Joshua Saxby
 *
 * See README.md for more information and LICENSE for licensing details.
 */

// protection against multiple includes
#ifndef SAXBOPHONE_RISKY_H
#define SAXBOPHONE_RISKY_H

#ifdef __cplusplus
extern "C"{
#endif

    // instruction opcodes enum
    typedef enum opcode {
        ADD = 0x0U,
        SUB = 0x1U,
        MUL = 0x2U,
        MOD = 0x3U,
        AND = 0x4U,
        NOT = 0x5U,
        OR = 0x6U,
        XOR = 0x7U,
        SAV = 0x8U,
        LOD = 0x9U,
        COP = 0xAU,
        SET = 0xBU,
        JMP = 0xCU,
        JIF = 0xDU,
        EQU = 0xEU,
        GRT = 0xFU
    } Opcode;

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
