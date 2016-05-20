/*#include "../../../../src/float/float_approx.h"*/
#include "../../../../src/float/error/erf.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../common/bench.h"

int main(int argc, const char *argv[])
{
    const uint32_t size = 131072;
    union bit32_u *numbers;
    float *res1;
    float *res2;

    res1    = malloc(size * sizeof(float));
    res2    = malloc(size * sizeof(float));
    numbers = malloc(size * sizeof(float));

    gen_numbers_new(numbers, 
             (FLT_SIGNIFICAND_MASK+1), (FLT_EXPONENT_MASK -1), size);

    TIME_ALGORITHM_1_NEW(   erff, size, res1, numbers);
    TIME_ALGORITHM_1_NEW(my_erff, size, res2, numbers);

    test_results(res1, res2, (float *)numbers, size, 0);
    printf("\n");
    statistic_results(res1, res2, size);
    printf("\n");
    /*
     *check_algorithm(my_erff, erff,
     *        (FLT_SIGNIFICAND_MASK+1), (FLT_EXPONENT_MASK -1), 1);
     */

    free(numbers);
    free(res1);
    free(res2);

    return 0;
}
