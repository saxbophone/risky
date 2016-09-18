/*
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
        case JMP:
            // JMP takes one register as its only argument
            extract_instruction_fields(
                raw, instruction, false, false, false, true, false, false, false
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
