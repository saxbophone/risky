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

    // Creates and returns a new blank risky state struct
    risky_state_t risky_init() {
        // initialised to all zeros by default
        risky_state_t state = {};
        return state;
    }

    // Given a file path and a risky state struct, attempts to load the file
    // contents into the memory of the risky state. Returns true on success,
    // false on failure to read or load the file into memory.
    bool
    risky_boot(char filepath[], risky_state_t * state) {
        // buffer to read into temporarily
        uint8_t buffer[65536];
        // try and open the file at the given file path in read binary mode
        FILE * file_handle = fopen(filepath, "rb");
        if(file_handle == NULL) {
            // couldn't open file, return false
            return false;
        } else {
            // we opened the file, now try and read 65536 bytes:
            size_t bytes_read = fread(&buffer, 1, 65536, file_handle);
            // check if we read the correct number of bytes
            if(bytes_read == 65536) {
                // we read exactly 65536 bytes,
                // so we can now copy these to machine ram
                for(int i = 0; i < 256; i++) {
                    for(int j = 0; j < 256; j++) {
                        state->ram[i][j] = buffer[((i * 256) + j) % 65536];
                    }
                }
                // finally return true so we know boot from file was successful
                return true;
            } else {
                // if we read less (or more) than 256 bytes,
                // then something went wrong
                return false;
            }
        }
    }

    // Populates a byte array with the raw bytes that represent an instruction_t
    void
    instruction_to_raw(
        instruction_t instruction, instruction_raw_t * raw_instruction
    ) {
        // The instruction is processed 4 bits at a time,
        // as that's the lowest value we care about. This makes sure
        // machine-specific endianness doesn't cause any problems.
        // bit mask the higher 4 bits
        raw_instruction[0] += (instruction.opcode << 4);
        // no bitmask needed, lower 4 bits
        raw_instruction[0] += instruction.primary;
        // second byte needs special handling:
        // if it's an instruction that deals with a literal value,
        // we can just copy it across. All other instructions operate on two
        // nibbles (4 bits) so these need to be handled differently.
        switch(instruction.opcode) {
            case SET:
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
    instruction_t
    instruction_from_raw(instruction_raw_t * raw_instruction) {
        // The instruction is processed 4 bits at a time,
        // as that's the lowest value we care about. This makes sure
        // machine-specific endianness doesn't cause any problems.
        instruction_t instruction = {};
        // bit mask the higher 4 bits
        instruction.opcode = (raw_instruction[0] & 0xF0U) >> 4;
        // bit mask the lower 4 bits
        instruction.primary = (raw_instruction[0] & 0x0FU);
        // second byte needs special handling:
        // if it's an instruction that deals with a literal value,
        // we can just copy it across. All other instructions operate on two
        // nibbles (4 bits) so these need to be handled differently.
        switch(instruction.opcode) {
            case SET:
                // just copy across
                instruction.operands.literal_value = raw_instruction[1];
                break;
            default:
                // split up into two nibbles
                // bit mask the higher 4 bits
                instruction.operands.registers.a = (
                    (raw_instruction[1] & 0xF0U) >> 4
                );
                // bit mask the lower 4 bits
                instruction.operands.registers.b = (
                    raw_instruction[1] & 0x0FU
                );
        }
        return instruction;
    }

    // Converts an array of two uint8_t to one uin16_t, big-endian
    uint16_t
    bytes_to_short(uint8_t * bytes) {
        // init result
        uint16_t result = 0;
        // add higer byte
        result += (bytes[0] << 8);
        // ad lower byte
        result += bytes[1];
        return result;
    }

    // Converts one uint16_t to an array of two uint8_t, big-endian
    void
    short_to_bytes(uint16_t single, uint8_t * bytes) {
        // clear array
        bytes[0] = 0;
        bytes[1] = 0;
        // split higher byte
        bytes[0] = ((single & 0xFF00U) >> 8);
        // split lower byte
        bytes[1] = (uint8_t)(single & 0x00FFU);
    }

    // execute a functional instruction and store the value of the result in
    // risky_state_t state. returns true / false on success / error
    bool
    function_operation(instruction_t instruction, risky_state_t * state) {
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
                // we should never get here, but if we do then error
                return false;
        }
        // store result in result register
        state->registers[instruction.primary] = result;
        // return success
        return true;
    }

    // execute a memory or register operation, manipulating state as necessary
    // returns false if given opcode was invalid
    bool
    memory_operation(instruction_t instruction, risky_state_t * state) {
        // allocate temporary variables
        // register indexes
        uint8_t primary = instruction.primary;
        uint8_t reg_a = instruction.operands.registers.a;
        uint8_t reg_b = instruction.operands.registers.b;
        // lookup register values for RAM addressing
        uint8_t val_a = state->registers[reg_a];
        uint8_t val_b = state->registers[reg_b];
        switch(instruction.opcode) {
            case SAV:
                // Save the value of a register to RAM
                state->ram[val_a][val_b] = state->registers[primary];
                break;
            case LOD:
                // Load a value from RAM to a register
                state->registers[primary] = state->ram[val_a][val_b];
                break;
            case COP:
                // Copy the value of one register to another register
                state->registers[primary] = state->registers[reg_a];
                break;
            case EQU:
                // compare if registers are equal or not,
                // write 0xff to result if true
                if(state->registers[reg_a] == state->registers[reg_b]) {
                    state->registers[primary] = 0xFFU;
                } else {
                    state->registers[primary] = 0x00U;
                }
                break;
            case GRT:
                // compare if register a is greater than b,
                // write 0xff to result if true
                if(state->registers[reg_a] > state->registers[reg_b]) {
                    state->registers[primary] = 0xFFU;
                } else {
                    state->registers[primary] = 0x00U;
                }
                break;
            default:
                // we should never get here, but if we do then error
                return false;
        }
        return true;
    }

    // Given a risky state struct, executes one instruction for this machine
    // state. returns true on success, false on error
    bool
    risky_run(risky_state_t * state) {
        // decode program counter array into 16 bit int for easier manipulation
        uint16_t first_address = bytes_to_short(state->program_counter);
        // calculate address of second byte in instruction, handle overflow
        uint16_t second_address = (first_address + 1) % 65536;
        // decode second address back to bytes
        uint8_t second_address_bytes[2] = {};
        short_to_bytes(second_address, second_address_bytes);
        // calculate address of next logical instruction
        // (our current address + instruction size), handle overflow
        uint16_t next_instruction = (first_address + 2) % 65536;
        // build byte addresses of next instruction
        uint8_t next_instruction_bytes[2] = {};
        short_to_bytes(next_instruction, next_instruction_bytes);
        // build temporary 2 item array to read the instruction bytes into
        instruction_raw_t buffer[2] = {
            state->ram[state->program_counter[0]][state->program_counter[1]],
            state->ram[second_address_bytes[0]][second_address_bytes[1]]
        };
        // build instruction from these bytes
        instruction_t instruction = instruction_from_raw(buffer);
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
                // try and run it and if it's not successful,
                // return false to indicate error.
                if(!function_operation(instruction, state)) {
                    return false;
                }
                break;
            case SAV:
            case LOD:
            case COP:
            case EQU:
            case GRT:
                // It's an operation that manipulates RAM or registers
                // try and run it and if it's not successful,
                // return false to indicate error.
                if(!memory_operation(instruction, state)) {
                    return false;
                }
                break;
            case JMP:
                // JUMP to the memory address in the instruction
                next_instruction_bytes[0]
                    = state->registers[instruction.operands.registers.a];
                next_instruction_bytes[1]
                    = state->registers[instruction.operands.registers.b];
                break;
            case JIF:
                // JUMP as above, but only if the primary register is non-zero
                if(state->registers[instruction.primary]) {
                    next_instruction_bytes[0]
                        = state->registers[instruction.operands.registers.a];
                    next_instruction_bytes[1]
                        = state->registers[instruction.operands.registers.b];
                }
                break;
            case SET:
                // Set the value of one register to a literal value
                state->registers[instruction.primary]
                    = instruction.operands.literal_value;
                break;
            default:
                // we should never get here, but if we do then error
                return false;
        }
        // if we're here then this means that the instruction was executed
        // correctly. set the program counter to the next instruction address
        state->program_counter[0] = next_instruction_bytes[0];
        state->program_counter[1] = next_instruction_bytes[1];
        return true;
    }

    // Given a risky state struct, print out a dump of the state's program
    // counter to stdout
    void
    dump_program_counter(risky_state_t * state) {
        printf(
            "| %02x%02x |", state->program_counter[0], state->program_counter[1]
        );
    }

    // Given a risky state struct, print out a dump of the state's registers
    // to stdout
    void
    dump_registers(risky_state_t * state) {
        printf("|");
        for(int i = 0; i < 16; i++) {
            printf(" %02x", state->registers[i]);
        }
        // end line
        printf(" |");
    }

    // // Given a risky state struct, print out a dump of the state's RAM
    // // to stdout
    // void
    // dump_ram(risky_state_t * state) {
    //     // not implemented
    // }

#ifdef __cplusplus
} // extern "C"
#endif
