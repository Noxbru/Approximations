#ifndef CBRT_H
#define CBRT_H
#pragma once

#include "../common/common.h"

/* 2 ulp of difference with cbrtf */
float my_cbrtf(float x)
{
    union bit32_u ui;
    float ret;
    float aux0, aux1;

    ui.f = x;

    /* Bit Magic! */
    ui.u = (ui.u/3) + 0x2A555556;

    ret = ui.f;

    /* three steps of Newton-Rapshon */

    aux0 = 2*ret + x/(ret * ret);
    aux0 /= 3;
    aux1 = 2*aux0 + x/(aux0 * aux0);
    aux1 /= 3;

    ret = 2*aux1 + x/(aux1 * aux1);
    ret /= 3;

    return ret;
}

#endif /* end of include guard: CBRT_H */
