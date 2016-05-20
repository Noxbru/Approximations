#ifndef LOG_H
#define LOG_H
#pragma once

#include <stdio.h>

#include "../common/common.h"

/*
 * Logic for this:
 * log(f) = log(m·r^s) = s·log(r) + log(m)
 *
 * given r = 2
 *
 * log(f) = s·log(2) + log(m)
 *
 * s can be extracted from the exponent as f >> 23
 *
 * m, if combined with an exponent of 127 will be a number
 * between 1 and 2, that says for how much you have to multiply
 * 2^s to get f, so you can approximate log(m):
 *
 * log(m) = log(1 + (m - 1)) ~ (m - 1) - (m - 1)^2 / 2 + ...
 *
 * This approach gives an error very high for numbers near the 'right side
 * of the interval' (numbers with m > 1.5) and we can do better for them.
 * The trick is trying to get an m between 0.5 and 1, so the approximation
 * for log(m) is good. We do that by using an exponent of 126.
 *
 * Another trick:
 *
 * log(m) = log([m^1/n]^n) = n·log(m^1/n) ~ n·[m^1/n - 1]
 */

float my_logf(float x)
{
    union bit32_u ui;
    float ret;
    float aux0, aux1;

    ui.f = x;
    int32_t val = ui.u;
    val >>= 23;

    /* Try to extract the significand as 1 + m */
    ui.u &= FLT_SIGNIFICAND_MASK;
    /*if(ui.u & 0x00400000U)*/
    /*if(ui.u > 0x002aaaabU) [> the significand of 4/3 <]*/
    if(ui.u > 0x003171f3U) /* the significand of 1.38629 = 2·log(2) */
    {
        ui.u |= 126 << 23;
        ret = (val - 126.0f) * 0.693147180559f;
    }
    else
    {
        ui.u |= 127 << 23;
        ret = (val - 127.0f) * 0.693147180559f;
    }
    /* [log2 : 2·log2]
     * [0.693147180559 : 1.38629436111] */

    /*printf("1: %f %f %x %f\n", x, ui.f, ui.u, ret);*/

    unsigned red = 0;

    /*if(fabs(ui.f - 1.0f) > 1e-1f)*/
    /*
     *while(fabs(ui.f - 1.0f) > 1.5e-1f)
     *{
     *    ui.f = sqrtf(ui.f);
     *    ping += 1;
     *}
     */
    ui.f -= 1;

    /*if(fabs(ui.f) > 1e-1f)*/
    while(fabs(ui.f) > 1e-1)
    {
        ui.f /= (1+sqrt(1+ui.f));
        red += 2;
    }
    /*printf("2: %f %x\n", ui.f, ui.u);*/
    /* 0.693147180559 -> 0.83255461 -> 0.9124443 -> 0.9552195 -> 0.97735331
     * 1.38629436111  -> 1.17741002 -> 1.0850852 -> 1.0416742 -> 1.02062444 */

    /*ui.f += -(ui.f * ui.f) / 2;*/
    /*ui.f += -(ui.f * ui.f) * (0.5 - ui.f / 3);*/
    /*ui.f += -(ui.f * ui.f) * (0.5 - ui.f * (1/3. - ui.f/4));*/
    /*ui.f += -(ui.f * ui.f) * (0.5f - ui.f * (1/3.0f - ui.f * (0.25f - ui.f/5.0f)));*/
    /*ui.f += -(ui.f * ui.f) * (0.5f - ui.f * (1/3.0f - ui.f * (0.25f - ui.f * (0.2f - ui.f/6.0f))));*/
    ui.f += -(ui.f * ui.f) * (0.5f - ui.f * (1/3.0f - ui.f * (0.25f - ui.f * (0.2f - ui.f * (1/6.0f - ui.f/7.0f)))));
    /*printf("3: %f %x\n", ui.f, ui.u);*/

    if(red) ui.f *= red;
    /*printf("4: %f %x\n", ui.f, ui.u);*/
    ret += ui.f;
    /*printf("5: %f\n", ret);*/


    /*
     *{
     *    aux0 = expf(-ret);
     *    aux1 = 1 - x * aux0;
     *    [>ret -= aux1 * (1 + aux1/2);<]
     *    ret -= aux1 * (1 + aux1 * (0.5 + aux1/3.));
     *}
     */
    /*
     *{
     *    aux0 = expf(ret);
     *    aux1 = (x - aux0) / (x + aux0);
     *    ret = ret + 2 * aux1;
     *}
     *{
     *    aux0 = expf(ret);
     *    aux1 = (x - aux0) / (x + aux0);
     *    ret = ret + 2 * aux1;
     *}
     */

    return ret;
}

float my_logf_agm(float x)
{
    union bit32_u ui;
    float ret;
    float aux0, aux1;
    float aux2, aux3;

    ui.f = x;
    int32_t val = ui.u;
    val >>= 23;
    val += 1 - 127;
    val = 12 - val;

    aux0 = 1;
    aux1 = pow(2, 2 - val) / x;

    do
    {
        aux2 = (aux0 + aux1) / 2;
        aux3 = sqrt(aux0 * aux1);

        aux0 = (aux2 + aux3) / 2;
        aux1 = sqrt(aux2 * aux3);
    } while(aux0 != aux2);

    aux0*=2;

    ret = M_PI/aux0 - val * 0.693147180559f;

    return ret;
}

#endif /* end of include guard: LOG_H */
