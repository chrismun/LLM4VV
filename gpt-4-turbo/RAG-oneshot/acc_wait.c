#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,async,wait,V:1.0-2.7
int test_async_wait(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel loop async(1)
        for (int x = 0; x < n; ++x){
            b[x] = a[x] * 2.0;
        }
        acc_wait(1);
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - (a[x] * 2.0)) > PRECISION){
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_async_wait();
    }
    if (failed != 0){
        printf("Test failed\n");
        failcode = failcode + (1 << 0);
    } else {
        printf("Test passed\n");
    }
#endif
    return failcode;
}