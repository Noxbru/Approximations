#ifndef RSQRTF_H
#define RSQRTF_H
#pragma once

#include "../common/common.h"

float my_rsqrtf(float x)
{
    float ret;
    float aux0, aux1;

    union bit32_u ui;

    ui.f = x;
    uint32_t val = ui.u;


    val = (val>>1) + 0x1FC00000;
    val = 0x7F000000 - val;

    ui.u = val;
    ret = ui.f;

    aux0 = ret + 1.0f/(x*ret);
    aux1 = aux0/4.0f + 1.0f/(x*aux0);
    ret = aux1 + 1.0f/(x*aux1);

    return ret / 2.0f;
}

#endif /* end of include guard: RSQRTF_H */
