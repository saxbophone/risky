#ifndef SAXBOPHONE_RISKY_DECODER_H
#include "core.h"
#include "risky.h"
#ifdef __cplusplus
extern "C"{
#endif
status_t decode_instruction_from_raw(
    risky_raw_instruction_t * raw, risky_instruction_t * instruction
);
#ifdef __cplusplus
}
#endif
#endif
