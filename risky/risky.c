/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2016, Joshua Saxby joshua.a.saxby+TNOPLuc8vM==@gmail.com
 *
 * risky - this compilation unit defines very generic / miscellaneous types
 * and values for the whole of RISKY.
 */
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
