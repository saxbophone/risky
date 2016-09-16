/*
 * risky - this compilation unit defines very generic / miscellaneous types
 * and values for the whole of RISKY.
 */
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
    STATUS_UNKNOWN = 0,
    MALLOC_REFUSED,
    IMPOSSIBLE_CONDITION,
    STATUS_SUCCESS,
} status_t;

// amount of RAM the RISKY VM has, in bytes
#define RISKY_RAM_AMOUNT 65536

extern const version_t VERSION;

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
