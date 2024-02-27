#include "acc_testsuite.h"  // Placeholder for common test suite definitions
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef T_CACHE
//T_CACHE:kernels,data,cache,V:1.0-2.7
int test_cache(){
    int err = 0;
    srand(SEED);
    real_t *A = (real_t *)malloc(n * sizeof(real_t));
    real_t *B = (real_t *)malloc(n * sizeof(real_t));
    real_t *C = (real_t *)malloc(n * sizeof(real_t));

    for (int i = 0; i < n; ++i){
        A[i] = rand() / (real_t)(RAND_MAX / 10);
        B[i] = rand() / (real_t)(RAND_MAX / 10);
        C[i] = 0.0;
    }

    #pragma acc data copyin(A[0:n],B[0:n]) copyout(C[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i){
                C[i] = A[i] + B[i];
            }
        }

        #pragma acc cache(A[0:n],B[0:n])
    }

    for (int i = 0; i < n; ++i){
        if (fabs(C[i] - (A[i] + B[i])) > PRECISION){
            err += 1;
        }
    }

    free(A);
    free(B);
    free(C);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T_CACHE
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_cache();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    printf("Test %s\n", failcode ? "FAILED" : "PASSED");
    return failcode;
}