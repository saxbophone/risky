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
        instruction_t instruction;
        instruction.opcode = (raw_instruction[0] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.primary = (raw_instruction[0] & 0x0FU); // bit mask the lower 4 bits
        instruction.operands.registers.a = (raw_instruction[1] & 0xF0U) >> 4; // bit mask the higher 4 bits
        instruction.operands.registers.b = (raw_instruction[1] & 0x0FU); // bit mask the lower 4 bits
        return instruction;
    }

    // Creates a new blank risky state struct
    risky_state_t risky_init() {
        risky_state_t state;
        // set program counter to 0
        state.program_counter = 0;
        // set all registers to 0
        for(int i = 0; i < 16; i++) {
            state.registers[i] = 0;
        }
        // set all RAM addresses to 0
        for(int i = 0; i < 256; i++) {
            state.ram[i] = 0;
        }
        return state;
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
            case SAV:
            case LOD:
            case COP:
            case SET:
            case JMP:
            case JIF:
            case EQU:
            case GRT:
                break;
            default:
                // Oh noes! Something went horribly wrong for us to get here!
                (void)0; // no-op for now
        }
        // finally, increment program counter by 2 (instruction length)
        state->program_counter += 2;
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

#ifdef __cplusplus
} // extern "C"
#endif
