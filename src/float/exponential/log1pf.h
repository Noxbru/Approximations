#ifndef LOG1P_H
#define LOG1P_H
#pragma once

#include "../common/common.h"
#include "logf.h"

/* log(1 + x) */
float my_log1pf(float x)
{
    float ret;
    unsigned int red = 0;

    /*if(fabs(x) > 1.2e-1f)*/
    if(fabs(x) > 1.2e-1f)
        return my_logf(1 + x);

    /*
     *while(fabs(x) > 1e-1)
     *{
     *    x /= (1+sqrt(1+x));
     *    red += 2;
     *}
     */

    ret = x;

    /*ret += -(ret * ret) / 2;*/
    /*ret += -(ret * ret) * (0.5 - ret / 3);*/
    /*ret += -(ret * ret) * (0.5 - ret * (1/3. - ret/4));*/
    /*ret += -(ret * ret) * (0.5f - ret * (1/3.0f - ret * (0.25f - ret/5.0f)));*/
    /*ret += -(ret * ret) * (0.5f - ret * (1/3.0f - ret * (0.25f - ret * (0.2f - ret/6.0f))));*/
    ret += -(ret * ret) * (0.5f - ret * (1/3.0f - ret * (0.25f - ret * (0.2f - ret * (1/6.0f - ret/7.0f)))));

    /*if(red) x *= red;*/

    return ret;
}

#endif /* end of include guard: LOG1P_H */
