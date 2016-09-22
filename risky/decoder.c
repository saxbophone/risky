/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Joshua Saxby joshua.a.saxby+TNOPLuc8vM==@gmail.com
 *
 * decoder - this compilation unit defines functions used for decoding binary
 * data into the instructions they represent
 */
#include <stdbool.h>

#include "core.h"
#include "decoder.h"
#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * private function - given a pointer to a risky_raw_instruction_t, a pointer to
 * a risky_instruction_t and flags specifying which instruction fields to read,
 * extract only the fields whose arguments are set to true and set these fields
 * on the instruction that is pointed to
 */
void extract_instruction_fields(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction,
    bool a_flag, bool b_flag, bool c_flag, bool r, bool a, bool b, bool l
) {
    // copy across the fields for which the function arguments are set to true
    if(a_flag) {
        // flag a is taken from the 6th bit of the first byte
        instruction->a_flag = (bool) (raw->bytes[0] & 0x04U);
    }
    if(b_flag) {
        // flag b is taken from the 7th bit of the first byte
        instruction->b_flag = (bool) (raw->bytes[0] & 0x02U);
    }
    if(c_flag) {
        // flag c is taken from the 8th bit of the first byte
        instruction->c_flag = (bool) (raw->bytes[0] & 0x01U);
    }
    if(r) {
        // 'return' register address is taken from the second byte as-is
        instruction->r = (risky_register_address_t) raw->bytes[1];
    }
    if(a) {
        // 'operand a' register address is taken from the third byte as-is
        instruction->a = (risky_register_address_t) raw->bytes[2];
    }
    if(b) {
        // 'operand b' register address is taken from the fourth byte as-is
        instruction->b = (risky_register_address_t) raw->bytes[3];
    }
    if(l) {
        /*
         * 'large' 16-bit value is taken from the third and fourth bytes
         * (big-endian format)
         */
        instruction->l = (risky_register_t) (raw->bytes[2] << 8) | raw->bytes[3];
    }
}

/*
 * given a pointer to a risky_raw_instruction_t and a pointer to a
 * risky_instruction_t, decode the raw instruction data and write the
 * instruction opcode, flags and operands to the risky_instruction_t.
 * returns a status_t with error / success information
 */
status_t decode_instruction_from_raw(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction
) {
    // set return status to success initially
    status_t result = STATUS_SUCCESS;
    // extract opcode from first 5 bits of first byte
    instruction->opcode = (risky_opcode_t) (raw->bytes[0] >> 3) % 32;
    // set all other fields to 0 initially
    instruction->a_flag = false;
    instruction->b_flag = false;
    instruction->c_flag = false;
    instruction->r = 0;
    instruction->a = 0;
    instruction->b = 0;
    instruction->l = 0;
    /*
     * now use switch-case on opcode to handle the various instructions
     * not all instructions use all flags and all operands
     */
    switch(instruction->opcode) {
        // rule-out operations that take no arguments first
        case NOP:
        case HLT:
            // quit switch early
            break;
        // JMP takes one register as its only argument
        case JMP:
            extract_instruction_fields(
                raw, instruction, false, false, false, true, false, false, false
            );
            break;
        // BRA takes one flag and two registers (r and a)
        case BRA:
            extract_instruction_fields(
                raw, instruction, true, false, false, true, true, false, false
            );
            break;
        /*
         * the following fall-through case statements catch instructions which
         * use all instruction fields (except the literal 16-bit value field)
         */
        case EQU:
        case NEQ:
        case GTN:
        case LTN:
        case ADD:
        case SUB:
        case MLT:
        case DIV:
        case MOD:
        case EOR:
        case AND:
        case XOR:
        case LSH:
        case RSH:
        case CAS:
        case QDC:
        case CDC:
            extract_instruction_fields(
                raw, instruction, true, true, true, true, true, true, false
            );
            break;
        /*
         * the following fall-through case statements catch instructions which
         * use two flags and two register operands
         */
        case INC:
        case DEC:
        case NOT:
        case ROT:
        case COP:
        case LOD:
        case SAV:
            extract_instruction_fields(
                raw, instruction, true, true, false, true, true, false, false
            );
            break;
        // the REA and WRI instructions use two register operands and no flags
        case REA:
        case WRI:
            extract_instruction_fields(
                raw, instruction, false, false, false, true, true, false, false
            );
            break;
        // QOP is a unique instruction that uses one register and all three flags
        case QOP:
            extract_instruction_fields(
                raw, instruction, true, true, true, true, false, false, false
            );
            break;
        /*
         * SET is a unique instruction that uses one register operand, one
         * 16-bit literal value (big-endian) and one flag
         */
        case SET:
            extract_instruction_fields(
                raw, instruction, true, false, false, true, false, false, true
            );
            break;
        // impossible to match none of the opcodes, but just in case
        default:
            result = IMPOSSIBLE_CONDITION;
            break;
    }
    return result;
}

#ifdef __cplusplus
} // extern "C"
#endif
