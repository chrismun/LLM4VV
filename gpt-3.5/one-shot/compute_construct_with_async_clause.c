#include "acc_testsuite.h"
#ifndef T2
//T2:parallel,async,V:2.7-2.7
int test2(){
    int err = 0;
    srand(SEED);
    
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }
    
    int async_count = 3;

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n]) async(async_count)
    {
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    #pragma acc wait(async_count)

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}