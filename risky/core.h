/*
 * core - this compilation unit defines the data types used for representing the
 * state of the RISKY virtual machine, and some functions for creating and
 * destroying objects of such types.
 */
#ifndef SAXBOPHONE_RISKY_CORE_H
#define SAXBOPHONE_RISKY_CORE_H

#include <stdbool.h>
#include <stdint.h>

#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

// register type
typedef risky_word_t risky_register_t;
// RAM type
typedef risky_byte_t risky_ram_t;

// risky vm state struct
typedef struct risky_vm_state_t {
    // 256 registers
    risky_register_t registers[RISKY_REGISTER_COUNT];
    // a pointer to a dynamically allocated array of RAM (65,536 bytes / 64KiB)
    risky_ram_t * ram;
} risky_vm_state_t;

// all RISKY opcodes
typedef enum risky_opcode_t {
    NOP, JMP, BRA, HLT, // no-op, jump, branch, halt
    EQU, NEQ, GTN, LTN, // equal?, not equal?, greater than?, less than?
    ADD, SUB, MLT, DIV, // add, subtract, multiply, divide
    MOD, INC, DEC, QOP, // modulo, increment, decrement, query last operation
    EOR, AND, XOR, NOT, // either or, and, exclusive or, not
    LSH, RSH, ROT, CAS, // left shift, right shift, rotate, cascade
    SET, COP, LOD, SAV, // set register, copy register, load memory, save memory
    QDC, CDC, REA, WRI, // query, configure, read from, write to (data channel)
} risky_opcode_t;

// register address type
typedef risky_byte_t risky_register_address_t;
// RAM address type
typedef risky_word_t risky_ram_address_t;

// risky instruction struct
typedef struct risky_instruction_t {
    risky_opcode_t opcode; // instruction opcode
    // additional instruction flags
    bool a_flag, b_flag, c_flag;
    // 'return register' and other main operands
    risky_register_address_t r, a, b;
    // the other possible 16-bit memory address / literal value operand
    risky_register_t l;
} risky_instruction_t;

// struct storing raw bytes for an instruction
typedef struct risky_raw_instruction_t {
    risky_byte_t bytes[4];
} risky_raw_instruction_t;

/*
 * given a pointer to a risky_vm_state_t, initialises the state struct,
 * allocates memory, etc...
 * Returns a status_t with error / success information
 */
status_t init_risky_vm_state(risky_vm_state_t * state);

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
