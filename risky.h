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

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

    // raw instruction type
    typedef uint8_t instruction_raw_t;

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

    // risky virtual machine state struct, stores the entire state of the machine
    typedef struct {
        uint8_t program_counter; // stores index of currently executing instruction in RAM
        uint8_t registers[16]; // 16 8-bit registers at our disposal
        uint8_t ram[256]; // 256 bytes of RAM at our disposal!
    } risky_state_t;

    // Populates a byte array with the raw bytes that represent an instruction struct
    void instruction_to_raw(instruction_t instruction, instruction_raw_t * raw_instruction);

    // Creates and returns a new instruction struct from raw bytes
    instruction_t instruction_from_raw(instruction_raw_t * raw_instruction);

    // execute a functional instruction and store the value of the result in state
    // returns true / false on success / error
    bool function_operation(instruction_t instruction, risky_state_t * state);

    // execute a pure register-to-register operation, manipulating state as necessary
    // returns false if given opcode was invalid
    bool register_operation(instruction_t instruction, risky_state_t * state);

    // execute a memory operation, manipulating state as necessary
    // returns false if given opcode was invalid
    bool memory_operation(instruction_t instruction, risky_state_t * state);

    // Creates and returns a new blank risky state struct
    risky_state_t risky_init();

    // Given a file path and a risky state struct, attempts to load the file
    // contents into the memory of the risky state.
    // Returns true on success, false on failure to read or load the file into memory.
    bool risky_boot(char filepath[], risky_state_t * state);

    // Given a risky state struct, executes one instruction for this machine state
    // returns true on success, false on error
    bool risky_run(risky_state_t * state);

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
