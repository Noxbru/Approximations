#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#define FLT_SIGN_MASK           0x80000000U
#define FLT_EXPONENT_MASK       0x7F800000U
#define FLT_SIGNIFICAND_MASK    0x007FFFFFU

union bit32_u
{
    uint32_t u;
    int32_t i;
    float f;
};

#endif /* end of include guard: COMMON_H */
