#ifndef SAXBOPHONE_RISKY_CORE_H
#define SAXBOPHONE_RISKY_CORE_H

#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

typedef struct version_t {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} version_t;

extern const version_t VERSION;

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
