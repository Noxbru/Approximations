#ifndef ERF_H
#define ERF_H
#pragma once

#include <math.h>

#include "../common/common.h"

float my_erff(float x)
{
    float xx, ret;
    float aux0, aux1;

    xx = fabs(x);

    if(xx > 3.92)
        ret = 1;
    else if(xx > 0.6)
    {
        float t;
        const float
            p  =  0.3275911f,
            a0 =  0.254829592f,
            a1 = -0.284496736f,
            a2 =  1.421413741f,
            a3 = -1.453152027f,
            a4 =  1.061405429f;

        t = 1.0f / (1.0f + p * xx);

        aux0 = t * EXPAND_POLY5(t, a0, a1, a2, a3, a4);

        aux1 = expf(-x*x);

        ret = 1.0f - aux0 * aux1;
    }
    else
    {
        const float
            a0 =  1.0f,
            a1 = -1/   3.0f,
            a2 =  1/  10.0f,
            a3 = -1/  42.0f,
            a4 =  1/ 216.0f,
            a5 = -1/1320.0f;
        aux0 = x * x;

        ret = M_2_SQRTPI * xx * EXPAND_POLY6(aux0, a0, a1, a2, a3, a4, a5);
    }
    
    ret = copysignf(ret, x);
    return ret;
}

float my_erff2(float x)
{
    float xx, ret;
    float aux0, aux1;

    const float
        a0 = M_2_SQRTPI *   31/ 200.0f,
        a1 = M_2_SQRTPI * -341/8000.0f;

    xx = fabs(x);

    aux0 = expf(-x * x);
    aux1 = sqrtf(1 - aux0);
    
    ret = aux1 * EXPAND_POLY3(aux0, 1.0f, a0, a1);

    ret = copysignf(ret, x);
    return ret;
}

float my_erff3(float x)
{
    float xx, ret;
    float aux0;

    const float
        a0 = 0.278393f,
        a1 = 0.230389f,
        a2 = 0.000972f,
        a3 = 0.078108f;

    xx = fabs(x);

    aux0 = EXPAND_POLY5(xx, 1.0f, a0, a1, a2, a3);

    ret = 1.0f - 1.0f / powf(aux0, 4);
    
    ret = copysignf(ret, x);
    return ret;
}

float my_erff4(float x)
{
    float xx, ret;
    float t;
    float aux0, aux1;

    const float
        p  =  0.47047f,
        a0 =  0.3480242f,
        a1 = -0.0958798f,
        a2 =  0.7478556f;

    xx = fabs(x);

    t = 1.0f / (1.0f + p * xx);

    aux0 = t * EXPAND_POLY3(t, a0, a1, a2);

    aux1 = expf(-x*x);

    ret = 1.0f - aux0 * aux1;
    
    ret = copysignf(ret, x);
    return ret;
}

float my_erff5(float x)
{
    float xx, ret;
    float aux0;

    const float
        a0 = 0.0705230784f,
        a1 = 0.0422820123f,
        a2 = 0.0092705272f,
        a3 = 0.0001520143f,
        a4 = 0.0002765672f,
        a5 = 0.0000430638f;

    xx = fabs(x);

    aux0 = EXPAND_POLY7(xx, 1.0f, a0, a1, a2, a3, a4, a5);

    ret = 1.0f - 1.0f / powf(aux0, 16);
    
    ret = copysignf(ret, x);
    return ret;
}

float my_erff6(float x)
{
    float xx, ret;
    float t;
    float aux0, aux1;

    const float
        p  =  0.3275911f,
        a0 =  0.254829592f,
        a1 = -0.284496736f,
        a2 =  1.421413741f,
        a3 = -1.453152027f,
        a4 =  1.061405429f;

    xx = fabs(x);

    t = 1.0f / (1.0f + p * xx);

    aux0 = t * EXPAND_POLY5(t, a0, a1, a2, a3, a4);

    aux1 = expf(-x*x);

    ret = 1.0f - aux0 * aux1;
    
    ret = copysignf(ret, x);
    return ret;
}

#endif /* end of include guard: ERF_H */
