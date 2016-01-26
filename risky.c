/*
 * RISKY
 *
 * A tiny virtual processor with a RISC-inspired instruction set
 *
 * Copyright (c) 2016 Joshua Saxby
 *
 * See README.md for more information and LICENSE for licensing details.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "risky.h"

#ifdef __cplusplus
extern "C"{
#endif

    // Populates a byte array with the raw bytes that represent an instruction struct
    void instruction_to_raw(instruction_t instruction, instruction_raw_t * raw_instruction) {
        // The instruction is processed 4 bits at a time, as that's the lowest value we care about.
        // This makes sure machine-specific endianness doesn't cause any problems.
        raw_instruction[0] += (instruction.opcode << 4); // bit mask the higher 4 bits
        raw_instruction[0] += instruction.primary; // no bitmask needed, lower 4 bits
        // second byte needs special handling:
        // if it's an instruction that deals with a memory address or a literal value,
        // we can just copy it across. All other instructions operate on two nibbles
        // (4 bits) so these need to be handled differently.
        switch(instruction.opcode) {
            case SAV:
            case LOD:
            case SET:
            case JMP:
            case JIF:
                // just copy across
                raw_instruction[1] = instruction.operands.literal_value;
                break;
            default:
                // asemble byte from two nibbles
                raw_instruction[1] += (instruction.operands.registers.a << 4);
                raw_instruction[1] += (instruction.operands.registers.b);
        }
    }

    // Creates and returns a new instruction struct from raw bytes
    instruction_t instruction_from_raw(instruction_raw_t * raw_instruction) {
        // The instruction is processed 4 bits at a time, as that's the lowest value we care about.
        // This makes sure machine-specific endianness doesn't cause any problems.
        instruction_t instruction = {};
        instruction.opcode = (raw_instruction[0] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.primary = (raw_instruction[0] & 0x0FU); // bit mask the lower 4 bits
        // second byte needs special handling:
        // if it's an instruction that deals with a memory address or a literal value,
        // we can just copy it across. All other instructions operate on two nibbles
        // (4 bits) so these need to be handled differently.
        switch(instruction.opcode) {
            case SAV:
            case LOD:
            case SET:
            case JMP:
            case JIF:
                // just copy across
                instruction.operands.literal_value = raw_instruction[1];
                break;
            default:
                // split up into two nibbles
                instruction.operands.registers.a = ((raw_instruction[1] & 0xF0U) >> 4); // bit mask the higher 4 bits
                instruction.operands.registers.b = (raw_instruction[1] & 0x0FU); // bit mask the lower 4 bits
        }
        return instruction;
    }

    // execute a functional instruction and store the value of the result in state
    // returns true / false on success / error
    bool function_operation(instruction_t instruction, risky_state_t * state) {
        // collect / allocate temporary variables
        uint8_t result;
        uint8_t a = state->registers[instruction.operands.registers.a];
        uint8_t b = state->registers[instruction.operands.registers.b];
        switch(instruction.opcode) {
            case ADD:
                result = a + b;
                break;
            case SUB:
                result = a - b;
                break;
            case MUL:
                result = a * b;
                break;
            case MOD:
                // if b is zero, return false as can't mod by 0
                if(b == 0) {
                    return false;
                } else {
                    result = a % b;
                }
                break;
            case AND:
                result = a & b;
                break;
            case NOT:
                result = ~ a;
                break;
            case OR:
                result = a | b;
                break;
            case XOR:
                result = a ^ b;
                break;
            default:
                // we should never get here, but if we do for some reason then error
                return false;
        }
        // store result in result register
        state->registers[instruction.primary] = result;
        // return success
        return true;
    }

    // execute a pure register-to-register operation, manipulating state as necessary
    // returns false if given opcode was invalid
    bool register_operation(instruction_t instruction, risky_state_t * state) {
        // allocate temporary variables
        uint8_t primary = instruction.primary;
        uint8_t reg_a = instruction.operands.registers.a;
        uint8_t reg_b = instruction.operands.registers.b;
        switch(instruction.opcode) {
            case COP:
                // Copy the value of one register to another register
                state->registers[primary] = state->registers[reg_a];
                break;
            case EQU:
                // compare if registers are equal or not, write 0xff to result if true
                if(state->registers[reg_a] == state->registers[reg_b]) {
                    state->registers[primary] = 0xFFU;
                } else {
                    state->registers[primary] = 0x00U;
                }
                break;
            case GRT:
                // compare if register a is greater than b, write 0xff to result if true
                if(state->registers[reg_a] > state->registers[reg_b]) {
                    state->registers[primary] = 0xFFU;
                } else {
                    state->registers[primary] = 0x00U;
                }
                break;
            default:
                // we should never get here, but if we do for some reason then error
                return false;
        }
        return true;
    }

    // execute a memory operation, manipulating state as necessary
    // returns false if given opcode was invalid
    bool memory_operation(instruction_t instruction, risky_state_t * state) {
        // allocate temporary variables
        uint8_t primary = instruction.primary;
        uint8_t memory_address = instruction.operands.memory_address;
        switch(instruction.opcode) {
            case SAV:
                // Save the value of a register to RAM
                state->ram[0][memory_address] = state->registers[primary];
                break;
            case LOD:
                // Load a value from RAM to a register
                state->registers[primary] = state->ram[0][memory_address];
                break;
            default:
                // we should never get here, but if we do for some reason then error
                return false;
        }
        return true;
    }

    // Creates and returns a new blank risky state struct
    risky_state_t risky_init() {
        // initialised to all zeros by default
        risky_state_t state = {};
        return state;
    }

    // Given a file path and a risky state struct, attempts to load the file
    // contents into the memory of the risky state.
    // Returns true on success, false on failure to read or load the file into memory.
    bool risky_boot(char filepath[], risky_state_t * state) {
        // buffer to read into temporarily
        uint8_t buffer[256];
        // try and open the file at the given file path in read binary mode
        FILE * file_handle = fopen(filepath, "rb");
        if(file_handle == NULL) {
            // couldn't open file, return false
            return false;
        } else {
            // we opened the file, now try and read 256 bytes:
            size_t bytes_read = fread(&buffer, 1, 256, file_handle);
            // check if we read the correct number of bytes
            if(bytes_read == 256) {
                // we read exactly 256 bytes, so we can now copy these to machine ram
                for(int i = 0; i < 256; i++) {
                    state->ram[0][i] = buffer[i];
                }
                // finally return true so we know boot from file was successful
                return true;
            } else {
                // if we read less (or more) than 256 bytes, then something went wrong
                return false;
            }
        }
    }

    // Given a risky state struct, executes one instruction for this machine state
    // returns true on success, false on error
    bool risky_run(risky_state_t * state) {
        // build temporary two-item array to read the bytes of the instruction into
        instruction_raw_t buffer[2] = {
            state->ram[0][state->program_counter],
            state->ram[0][(state->program_counter + 1) % 256] // in case of overflow
        };
        // build instruction from these bytes
        instruction_t instruction = instruction_from_raw(buffer);
        // allocate variable to store next value of program counter
        // this is initially set to the address of the next logical instruction
        // (our current address + instruction size)
        uint8_t next_instruction = state->program_counter + 2;
        // use instruction opcode to execute the appropriate operation:
        switch(instruction.opcode) {
            case ADD:
            case SUB:
            case MUL:
            case MOD:
            case AND:
            case NOT:
            case OR:
            case XOR:
                // It's a mathematical or logical operation that works with two
                // registers and stores result in another register.
                // try and run it and if it's not successful, return false to indicate error.
                if(!function_operation(instruction, state)) {
                    return false;
                }
                break;
            case COP:
            case EQU:
            case GRT:
                // It's an operation that only manipulates registers
                // try and run it and if it's not successful, return false to indicate error.
                if(!register_operation(instruction, state)) {
                    return false;
                }
                break;
            case SAV:
            case LOD:
                // It's an operation that manipulates RAM and registers
                // try and run it and if it's not successful, return false to indicate error.
                if(!memory_operation(instruction, state)) {
                    return false;
                }
                break;
            case JMP:
                // JUMP to the memory address in the instruction
                next_instruction = instruction.operands.memory_address;
                break;
            case JIF:
                // JUMP as above, but only if the primary register is non-zero
                if(state->registers[instruction.primary]) {
                    next_instruction = instruction.operands.memory_address;
                }
                break;
            case SET:
                // Set the value of one register to a literal value in the instruction
                state->registers[instruction.primary] = instruction.operands.literal_value;
                break;
            default:
                // we should never get here, but if we do for some reason then error
                return false;
        }
        // if we're here then this means that the instruction was executed correctly
        // set the program counter to the address of the next instruction
        state->program_counter = next_instruction;
        return true;
    }

#ifdef __cplusplus
} // extern "C"
#endif
