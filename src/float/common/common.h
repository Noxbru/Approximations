#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define FLT_SIGN_MASK           0x80000000U
#define FLT_EXPONENT_MASK       0x7F800000U
#define FLT_SIGNIFICAND_MASK    0x007FFFFFU

#define EXPAND_POLY1(X, A) A
#define EXPAND_POLY2(X, A, ...) \
    (A + X * EXPAND_POLY1(X, __VA_ARGS__ ))
#define EXPAND_POLY3(X, A, ...) \
    (A + X * EXPAND_POLY2(X, __VA_ARGS__ ))
#define EXPAND_POLY4(X, A, ...) \
    (A + X * EXPAND_POLY3(X, __VA_ARGS__ ))
#define EXPAND_POLY5(X, A, ...) \
    (A + X * EXPAND_POLY4(X, __VA_ARGS__ ))
#define EXPAND_POLY6(X, A, ...) \
    (A + X * EXPAND_POLY5(X, __VA_ARGS__ ))
#define EXPAND_POLY7(X, A, ...) \
    (A + X * EXPAND_POLY6(X, __VA_ARGS__ ))

union bit32_u
{
    uint32_t u;
    int32_t i;
    float f;
};

static inline void print_float(float f)
{
    union bit32_u u;
    uint32_t i;
    uint32_t id = 1 << 31;
    char str[35];
    str[34] = '\0';
    u.f = f;

    str[0] = u.u & id ? '1' : '0';
    str[1] = ' ';

    for(i = 2, id >>= 1 ; i < 10; i++, id >>= 1)
        str[i] = (u.u & id) ? '1' : '0';
    str[i++] = ' ';

    for(; i < 34; i++, id >>= 1)
        str[i] = (u.u & id) ? '1' : '0';

    fputs(str, stdout);
}

#endif /* end of include guard: COMMON_H */
