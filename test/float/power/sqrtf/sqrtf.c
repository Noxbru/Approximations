#include "../../../../src/float/float_approx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../../common/bench.h"

int main(int argc, const char *argv[])
{
    float *numbers;
    float *res1;
    float *res2;

    numbers = gen_numbers();
    res1 = malloc(65536 * sizeof(float));
    res2 = malloc(65536 * sizeof(float));

    TIME_ALGORITHM_1(   sqrtf, 65536, res1, numbers);
    TIME_ALGORITHM_1(my_sqrtf, 65536, res2, numbers);

    test_results(res1, res2, numbers, 65536, 1);
    printf("\n");
    statistic_results(res1, res2, 65536);
    printf("\n");
    /*
     *check_algorithm(my_sqrtf, sqrtf,
     *        (FLT_SIGNIFICAND_MASK+1), (FLT_EXPONENT_MASK -1), 1);
     */

    free(numbers);
    free(res1);
    free(res2);

    return 0;
}
