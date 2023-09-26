#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t min = 0.0;

    for (int x = 0; x < 10; ++x){
        a[x] = rand() / (real_t)(RAND_MAX/n);
    }

    #pragma acc data copyin(a[0:10])
    {
        #pragma acc serial reduction(min:min)
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                min = fmin(a[x], min);
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        if (fabs(a[x] - min) > PRECISION){
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