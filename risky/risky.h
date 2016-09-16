#ifndef SAXBOPHONE_RISKY_RISKY_H
#define SAXBOPHONE_RISKY_RISKY_H

#include <stdint.h>


#ifdef __cplusplus
extern "C"{
#endif

// struct for representing version of RISKY
typedef struct version_t {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} version_t;

// enum for storing information about the error status of a function
typedef enum status_t {
    UNKNOWN = 0,
    MALLOC_REFUSED,
    IMPOSSIBLE_CONDITION,
    SUCCESS,
} status_t;

extern const version_t VERSION;

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
