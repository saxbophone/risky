#ifndef SAXBOPHONE_RISKY_CORE_H
#include <stdbool.h>
#include <stdint.h>
#include "risky.h"
#ifdef __cplusplus
extern "C"{
#endif
typedef risky_word_t risky_register_t;
typedef risky_byte_t risky_ram_t;
typedef struct risky_vm_state_t {
    risky_register_t registers[RISKY_REGISTER_COUNT];
    risky_ram_t * ram;
} risky_vm_state_t;
typedef enum risky_opcode_t {
    NOP, JMP, BRA, HLT,
    EQU, NEQ, GTN, LTN,
    ADD, SUB, MLT, DIV,
    MOD, INC, DEC, QOP,
    EOR, AND, XOR, NOT,
    LSH, RSH, ROT, CAS,
    SET, COP, LOD, SAV,
    QDC, CDC, REA, WRI,
} risky_opcode_t;
typedef risky_byte_t risky_register_address_t;
typedef risky_word_t risky_ram_address_t;
typedef struct risky_instruction_t {
    risky_opcode_t opcode;
    bool a_flag, b_flag, c_flag;
    risky_register_address_t r, a, b;
    risky_register_t l;
} risky_instruction_t;
typedef struct risky_raw_instruction_t {
    risky_byte_t bytes[4];
} risky_raw_instruction_t;
status_t init_risky_vm_state(risky_vm_state_t * state);
#ifdef __cplusplus
}
#endif
#endif
