#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct independent clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[10 * n];
    real_t * b = new real_t[10 * n];
    real_t * c = new real_t[10 * n];

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n; ++y){
                    c[x * n + y] = a[x * n + y] + b[x * n + y];
                }
            }
        }
    }
    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(c[x * n + y] - (a[x * n + y] + b[x * n + y])) > PRECISION){
                err = err + 1;
            }
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