#include "acc_testsuite.h"
#ifndef T1
//T1:data,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data create(a[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            {
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + 1;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - x - 1) > PRECISION){
            err = 1;
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