#include "acc_testsuite.h"
#ifndef T1
// T1:async,V:1.0-3.1
int test_wait_any(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    // Initialize arrays
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x] * 2;
        c[x] = 0;
    }

    // Perform async operations with two async tags
    #pragma acc kernels async(1) copyin(a[0:n]) copyout(c[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            c[i] = a[i];
        }
    }
    
    #pragma acc kernels async(2) copy(a[0:n])
    {
        #pragma acc loop
        for (int i = 0; i < n; ++i){
            a[i] *= 2;
        }
    }

    // Wait for any of the asynchronous operations to complete
    #pragma acc wait any(1, 2)

    // Check for correctness
    // Note: At least one of the operations should have completed.
    int completed_any = 0;
    for (int i = 0; i < n; ++i){
        if (fabs(c[i] - a[i]) <= PRECISION || fabs(a[i] - b[i]) <= PRECISION){
            completed_any = 1;
            break;
        }
    }

    if (!completed_any){
        err += 1;
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
        failed += test_wait_any();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}