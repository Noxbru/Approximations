#ifndef BENCH_H
#define BENCH_H

#include <time.h>
#include <stdio.h>

#include "common.h"

float *gen_numbers(void)
{
    unsigned int i;
    float delta =253./65535;
    float *n = malloc(65536 * sizeof(float));

    for(i = 0; i < 65536; i++)
        n[i] = pow(2,i*delta-126); // Fuck denormals !

    return n;
}

void gen_numbers_new(union bit32_u *numbers,
        uint32_t start, uint32_t end, uint32_t size)
{
    unsigned int i;
    uint32_t step = (end - start) / size;

    for(i = 0; i < size; i++)
        numbers[i].u = start + i * step;
    numbers[size - 1].u = end;
}

#define TIME_ALGORITHM_1(function, reps, out, in) \
    do { \
        struct timespec tp1, tp2; \
        unsigned long elapsed_time; \
        clock_gettime(CLOCK_MONOTONIC,&tp1); \
        { \
            for(unsigned i = 0; i < reps; i++) \
                out[i] = function(in[i]); \
        } \
        clock_gettime(CLOCK_MONOTONIC,&tp2); \
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec; \
        printf(#function":\t%lu\n",elapsed_time); \
    } while(0);

#define TIME_ALGORITHM_1_NEW(function, reps, out, in) \
    do { \
        struct timespec tp1, tp2; \
        unsigned long elapsed_time; \
        clock_gettime(CLOCK_MONOTONIC,&tp1); \
        { \
            for(unsigned i = 0; i < reps; i++) \
                out[i] = function(in[i].f); \
        } \
        clock_gettime(CLOCK_MONOTONIC,&tp2); \
        elapsed_time = (unsigned long) (tp2.tv_sec-tp1.tv_sec)*1000000000 + \
                       (unsigned long) tp2.tv_nsec-tp1.tv_nsec; \
        printf(#function":\t%lu\n",elapsed_time); \
    } while(0);

void test_results(float *res1, float *res2, float *numbers,
        uint32_t size, uint32_t tolerance)
{
    unsigned int i;

    for(i = 0; i < size; i++)
    {
        union bit32_u ret1, ret2;
        union bit32_u u, n;

        ret1.f = res1[i];
        ret2.f = res2[i];

        u.u = ret1.u > ret2.u ?
            (ret1.u - ret2.u) :
            (ret2.u - ret1.u);

        n.f = numbers[i];

        if(u.u > tolerance || tolerance == 0xffffffff)
        {
            fprintf(stderr,"0x%08x\t%.5g:\t", n.u, n.f);
            fprintf(stderr,"0x%08x\t%.5g\t", ret1.u, ret1.f);
            fprintf(stderr,"0x%08x\t%.5g\t", ret2.u, ret2.f);
            fprintf(stderr,"0x%08x\t%.5g\n", u.u, (res1[i] - res2[i])/res1[i]);
        }
    }
}

void statistic_results(float *res1, float *res2, uint32_t size)
{
    unsigned int i;
    float max_diff = 0.0f;
    float mean_diff = 0.0f;

    for(i = 0; i < size; i++)
    {
        float aux = fabs((res1[i] - res2[i]) / res1[i]);
        if(res1[i] == 0) continue;

        max_diff = fmax(max_diff, aux);
        mean_diff += aux;
    }
    mean_diff /= size;

    printf("max_diff:\t%g\n", max_diff);
    printf("mean_diff:\t%g\n", mean_diff);
}

void check_algorithm(float (*function)(float), float (*reference_function)(float),
        uint32_t start, uint32_t end, uint32_t tolerance)
{
    union bit32_u i, u;
    union bit32_u ret1, ret2;
    i.u = start;

    do
    {
        ret1.f = reference_function(i.f);
        ret2.f = function(i.f);

        u.u = ret1.u > ret2.u ?
            (ret1.u - ret2.u) :
            (ret2.u - ret1.u);

        if(u.u > tolerance || tolerance == 0xffffffff)
        {
            fprintf(stderr,"0x%08x\t%.5g:\t", i.u, i.f);
            fprintf(stderr,"0x%08x\t%.5g\t", ret1.u, ret1.f);
            fprintf(stderr,"0x%08x\t%.5g\t", ret2.u, ret2.f);
            fprintf(stderr,"0x%08x\t%.5g\n", u.u, (ret1.f - ret2.f)/ret1.f);
        }

        i.u++;
    }
    while (i.u != end);
}


#endif /* end of include guard: BENCH_H */
