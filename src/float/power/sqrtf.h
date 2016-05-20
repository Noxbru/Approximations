#ifndef SQRTF_H
#define SQRTF_H
#pragma once

#include "../common/common.h"

float my_sqrtf(float x)
{
    union bit32_u ui;
    float ret;
    float aux0, aux1;

    ui.f = x;

    /* Bit Magic! */
    ui.u = (ui.u>>1) + 0x1FC00000;

    ret = ui.f;

    /* three steps of Newton-Rapshon */
    aux0 = ret + x/ret;
    aux1 = aux0/4.0f + x/aux0;
    ret = aux1 + x/aux1;

    return ret / 2.0f;
}

#endif /* end of include guard: SQRTF_H */
