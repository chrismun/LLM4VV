#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,async,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }

        #pragma acc parallel loop async(2)
        for (int x = 0; x < n; ++x){
            b[x] = b[x] * 2.0;
        }
    }

    #pragma acc wait(1)
    for (int x = 0; x < n; ++x){
        if (fabs(b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    #pragma acc wait(2)
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - 2.0 * a[x]) > PRECISION){
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