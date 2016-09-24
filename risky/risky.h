#ifndef SAXBOPHONE_RISKY_RISKY_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C"{
#endif
typedef struct version_t {
    uint8_t major;
    uint8_t minor;
    uint8_t patch;
} version_t;
typedef enum status_t {
    STATUS_UNKNOWN = 0,
    STATUS_FAIL,
    MALLOC_REFUSED,
    IMPOSSIBLE_CONDITION,
    STATUS_SUCCESS,
} status_t;
typedef uint8_t risky_byte_t;
typedef uint16_t risky_word_t;
extern const version_t VERSION;
#ifdef __cplusplus
}
#endif
#endif
