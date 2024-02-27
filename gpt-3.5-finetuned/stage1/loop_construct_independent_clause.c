#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct independent clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t a[10], b[10], c[10], d[10];
    for (int x = 0; x < 10; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = c[x];
    }

    #pragma acc data copyin(a[0:10], b[0:10]) copyout(c[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < 10; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
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