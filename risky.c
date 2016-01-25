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
        raw_instruction[1] += (instruction.operands.registers.a << 4); // bit mask the higher 4 bits
        raw_instruction[1] += (instruction.operands.registers.b); // no bitmask needed, lower 4 bits
    }

    // Creates and returns a new instruction struct from raw bytes
    instruction_t instruction_from_raw(instruction_raw_t * raw_instruction) {
        // The instruction is processed 4 bits at a time, as that's the lowest value we care about.
        // This makes sure machine-specific endianness doesn't cause any problems.
        instruction_t instruction = {};
        instruction.opcode = (raw_instruction[0] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.primary = (raw_instruction[0] & 0x0FU); // bit mask the lower 4 bits
        instruction.operands.registers.a = (raw_instruction[1] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.operands.registers.b = (raw_instruction[1] & 0x0FU); // bit mask the lower 4 bits
        return instruction;
    }

    uint8_t function_operation(
        instruction_opcode_e opcode, literal_value_t a, literal_value_t b
    ) {
        uint8_t result;
        switch(opcode) {
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
                // if b is zero, set result to 0 - this is to avoid modulo by zero error
                if(b == 0) {
                    result = 0x00U;
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
                result = 0x00U;
        }
        return result;
    }

    // Creates a new blank risky state struct
    risky_state_t risky_init() {
        // initialised to all zeros by default
        risky_state_t state = {};
        return state;
    }

    // Prints a HEX dump of machine's program counter, registers and RAM.
    void risky_dump(risky_state_t * state) {
        printf("-----------------------------------------------\n");
        printf("RISKY Virtual Machine Memory Dump\n");
        printf("Program Counter: %02X\n", state->program_counter);
        printf("Registers:\n");
        for(int i = 0; i < 16; i++) {
            printf("%02X ", state->registers[i]);
        }
        printf("\n");
        printf("Memory:\n");
        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                printf("%02X ", state->ram[(i * 16) + j]);
            }
            printf("\n");
        }
        printf("-----------------------------------------------\n");
    }

    // Prints an error message to stderr, dumps machine state and aborts.
    void risky_err(risky_state_t * state, char message[]) {
        // print error message to stderr
        fprintf(stderr, "%s\n", message);
        // dump machine state
        risky_dump(state);
        // abort, because exit() is too lame
        abort();
    }

    // Given a risky state struct, executes one instruction for this machine state
    void risky_run(risky_state_t * state) {
        // build temporary two-item array to read the bytes of the instruction into
        instruction_raw_t buffer[2] = {
            state->ram[state->program_counter],
            state->ram[(state->program_counter + 1) % 256] // in case of overflow
        };
        // build instruction from these bytes
        instruction_t instruction = instruction_from_raw(buffer);
        // increment program counter by 2 (instruction length) in preparation for next one
        state->program_counter += 2;
        // use instruction opcode to execute the appropriate operation:
        // TODO: Implement execution of actual instructions
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
                // registers and stores result in another register
                state->registers[instruction.primary] = function_operation(
                    instruction.opcode,
                    state->registers[instruction.operands.registers.a],
                    state->registers[instruction.operands.registers.b]
                );
                break;
            case SAV:
                // Save the value of a register to RAM
                state->ram[instruction.operands.memory_address] = state->registers[instruction.primary];
                break;
            case LOD:
                // Load a value from RAM to a register
                state->registers[instruction.primary] = state->ram[instruction.operands.memory_address];
                break;
            case COP:
                // Copy the value of one register to another register
                state->registers[instruction.primary] = state->registers[instruction.operands.registers.a];
                break;
            case SET:
                // Set the value of one register to a literal value in the instruction
                state->registers[instruction.primary] = instruction.operands.literal_value;
                break;
            case JMP:
                // JUMP to the memory address in the instruction
                state->program_counter = instruction.operands.memory_address;
                break;
            case JIF:
                // JUMP as above, but only if the primary register is non-zero
                if(state->registers[instruction.primary]) {
                    state->program_counter = instruction.operands.memory_address;
                }
                break;
            case EQU:
                // compare if registers are equal or not, write 0xff to result if true
                if(state->registers[instruction.operands.registers.a] == state->registers[instruction.operands.registers.b]) {
                    state->registers[instruction.primary] = 0xFFU;
                } else {
                    state->registers[instruction.primary] = 0x00U;
                }
                break;
            case GRT:
                // compare if register a is greater than b, write 0xff to result if true
                if(state->registers[instruction.operands.registers.a] > state->registers[instruction.operands.registers.b]) {
                    state->registers[instruction.primary] = 0xFFU;
                } else {
                    state->registers[instruction.primary] = 0x00U;
                }
                break;
            default:
                // Oh noes! Something went horribly wrong for us to get here!
                risky_err(state, "FATAL: Instruction not found.");
        }
    }

#ifdef __cplusplus
} // extern "C"
#endif
