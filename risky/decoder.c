/*
 * decoder - this compilation unit defines functions used for decoding binary
 * data into the instructions they represent
 */
#include "core.h"
#include "decoder.h"
#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

/*
 * given a pointer to a risky_raw_instruction_t and a pointer to a
 * risky_instruction_t, decode the raw instruction data and write the
 * instruction opcode, flags and operands to the risky_instruction_t.
 * returns a status_t with error / success information
 */
status_t decode_instruction_from_raw(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction
) {
    // copy across opcode
    instruction->opcode = (risky_opcode_t)(raw->bytes[0] >> 3) % 32;
    // set all other fields to 0
    instruction->a_flag = false;
    instruction->b_flag = false;
    instruction->c_flag = false;
    instruction->r = 0;
    instruction->a = 0;
    instruction->b = 0;
    instruction->l = 0;
    status_t result = STATUS_SUCCESS;
    return result;
}

#ifdef __cplusplus
} // extern "C"
#endif
