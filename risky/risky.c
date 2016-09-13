#include "risky.h"


#ifdef __cplusplus
extern "C"{
#endif

// Version numbers are passed as preprocessor definitions by CMake
const version_t VERSION = {
    .major = RISKY_VERSION_MAJOR,
    .minor = RISKY_VERSION_MINOR,
    .patch = RISKY_VERSION_PATCH,
};

#ifdef __cplusplus
} // extern "C"
#endif
