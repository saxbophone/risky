/*
 * risky - this compilation unit defines very generic / miscellaneous types
 * and values for the whole of RISKY.
 */
#ifndef SAXBOPHONE_RISKY_RISKY_H
#define SAXBOPHONE_RISKY_RISKY_H

#include <stddef.h>
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
    STATUS_FAIL,
    MALLOC_REFUSED,
    IMPOSSIBLE_CONDITION,
    STATUS_SUCCESS,
} status_t;

// byte and word types for RISKY
typedef uint8_t risky_byte_t;
typedef uint16_t risky_word_t;

// number of registers
#define RISKY_REGISTER_COUNT 256
// amount of RAM the RISKY VM has, in bytes
#define RISKY_RAM_AMOUNT 65536

extern const version_t VERSION;

#ifdef __cplusplus
} // extern "C"
#endif

// end of header file
#endif
