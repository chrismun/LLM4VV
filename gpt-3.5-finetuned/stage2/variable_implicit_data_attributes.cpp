#include "acc_testsuite.h"
#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1()
{
    int err = 0;
    srand(SEED);
    int test_array[10];
    for (int number_of_loops = 0; number_of_loops < 10; ++number_of_loops)
    {
        test_array[number_of_loops] = (rand() / (real_t)(RAND_MAX / 10));
    }

    {
        int ga = 0, la = 0;
        int * ra = (int *)malloc(n * sizeof(int));
        ra[0] = ga + la + test_array[0];
#pragma acc loop reduction(+: ga)
        for (int number_of_loops = 0; number_of_loops < 10; ++number_of_loops)
        {
            ga = ga + test_array[number_of_loops];
        }
#pragma acc loop reduction(+: la)
        for (int number_of_loops = 0; number_of_loops < 10; ++number_of_loops)
        {
            la = la + test_array[number_of_loops];
        }

        if (ga != la || ga != test_array[1])
        {
            err += 1;
        }
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}