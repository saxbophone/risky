#include <stdbool.h>
#include "core.h"
#include "decoder.h"
#include "risky.h"
#ifdef __cplusplus
extern "C"{
#endif
void extract_instruction_fields(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction,
    bool a_flag, bool b_flag, bool c_flag, bool r, bool a, bool b, bool l
) {
    if(a_flag) {
        instruction->a_flag = (bool) (raw->bytes[0] & 0x04U);
    }
    if(b_flag) {
        instruction->b_flag = (bool) (raw->bytes[0] & 0x02U);
    }
    if(c_flag) {
        instruction->c_flag = (bool) (raw->bytes[0] & 0x01U);
    }
    if(r) {
        instruction->r = (risky_register_address_t) raw->bytes[1];
    }
    if(a) {
        instruction->a = (risky_register_address_t) raw->bytes[2];
    }
    if(b) {
        instruction->b = (risky_register_address_t) raw->bytes[3];
    }
    if(l) {
        instruction->l = (risky_register_t) (raw->bytes[2] << 8) | raw->bytes[3];
    }
}
status_t decode_instruction_from_raw(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction
) {
    status_t result = STATUS_SUCCESS;
    instruction->opcode = (risky_opcode_t) (raw->bytes[0] >> 3) % 32;
    instruction->a_flag = false;
    instruction->b_flag = false;
    instruction->c_flag = false;
    instruction->r = 0;
    instruction->a = 0;
    instruction->b = 0;
    instruction->l = 0;
    switch(instruction->opcode) {
        case NOP:
        case HLT:
            break;
        case JMP:
            extract_instruction_fields(
                raw, instruction, false, false, false, true, false, false, false
            );
            break;
        case BRA:
            extract_instruction_fields(
                raw, instruction, true, false, false, true, true, false, false
            );
            break;
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
        case REA:
        case WRI:
            extract_instruction_fields(
                raw, instruction, false, false, false, true, true, false, false
            );
            break;
        case QOP:
            extract_instruction_fields(
                raw, instruction, true, true, true, true, false, false, false
            );
            break;
        case SET:
            extract_instruction_fields(
                raw, instruction, true, false, false, true, false, false, true
            );
            break;
        default:
            result = IMPOSSIBLE_CONDITION;
            break;
    }
    return result;
}
#ifdef __cplusplus
}
#endif
