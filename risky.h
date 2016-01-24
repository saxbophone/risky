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

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

    // raw instruction type (2 unsigned bytes)
    typedef uint8_t instruction_raw_t[2];

    // instruction opcodes enum
    typedef enum {
        ADD = 0x0U, SUB = 0x1U, MUL = 0x2U, MOD = 0x3U,
        AND = 0x4U, NOT = 0x5U, OR = 0x6U,  XOR = 0x7U,
        SAV = 0x8U, LOD = 0x9U, COP = 0xAU, SET = 0xBU,
        JMP = 0xCU, JIF = 0xDU, EQU = 0xEU, GRT = 0xFU
    } instruction_opcode_e;

    // instruction opcode type (restricted to 4 bits in struct)
    typedef uint8_t instruction_opcode_t;

    // // register address type (restricted to 4 bits in struct)
    typedef uint8_t register_address_t;

    // memory address type
    typedef uint8_t memory_address_t;

    // literal value type
    typedef uint8_t literal_value_t;

    // registers struct, used for packing two register operands into a byte
    typedef struct {
        register_address_t a : 4; // restricted to 4 bits
        register_address_t b : 4; // restricted to 4 bits
    } registers_t;

    // operands union, used for the second byte of an instruction
    typedef union instruction_operands_t {
        memory_address_t memory_address; // an 8-bit memory address
        literal_value_t literal_value; // an 8-bit literal value
        registers_t registers; // two 4-bit registers
    } instruction_operands_t;

    // instruction type, used to represent a whole instruction
    typedef struct {
        instruction_opcode_t opcode : 4; // restricted to 4 bits
        register_address_t primary : 4; // primary reg for result/destination/source
        instruction_operands_t operands; // instruction_operands_t is 8 bits
    } instruction_t;

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif