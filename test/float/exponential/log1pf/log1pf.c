#include "../../../../src/float/float_approx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../common/bench.h"

int main(int argc, const char *argv[])
{
    union bit32_u *nn;
    float *numbers;
    float *res1;
    float *res2;

    /*
     *union bit32_u a, b;
     *a.f = -0.49;
     *b.f = -0.51;
     */

    /*
     *my_log1pf(a.f);
     *printf("%f\n",log1pf(a.f));
     *my_log1pf(b.f);
     *printf("%f\n",log1pf(b.f));
     *return 0;
     */

    numbers = gen_numbers();
    res1 = malloc(65536 * sizeof(float));
    res2 = malloc(65536 * sizeof(float));
    nn = malloc(65536 * sizeof(union bit32_u));
    gen_numbers_new(nn,
            (FLT_SIGNIFICAND_MASK + 1) | FLT_SIGN_MASK,
            (0x3f800000 - 1) | FLT_SIGN_MASK,
            65536);

    TIME_ALGORITHM_1(   log1pf, 65536, res1, numbers);
    TIME_ALGORITHM_1(my_log1pf, 65536, res2, numbers);

    test_results(res1, res2, numbers, 65536, 0);
    printf("\n");
    statistic_results(res1, res2, 65536);
    printf("\n");

    for(unsigned i = 0; i < 65536; i++)
    {
        res1[i] = log1pf(nn[i].f);
        res2[i] = my_log1pf(nn[i].f);
    }

    test_results(res1, res2, (float *)nn, 65536, 0);
    printf("\n");
    statistic_results(res1, res2, 65536);
    printf("\n");

    /*
     *check_algorithm(my_logf, logf,
     *        (FLT_SIGNIFICAND_MASK+1), (FLT_EXPONENT_MASK -1), 2);
     */
    /*
     *check_algorithm(my_logf, logf,
     *        0x3fb000ff, 0x3fb1f000, 0xffffffff);
     */
    /*
     *check_algorithm(my_log1pf, log1pf,
     *        0x3f21246e, 0x3fc5feeb, 2);
     */

    return 0;
}
