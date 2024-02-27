#include "acc_testsuite.h"
#ifndef T1
// T1:kernels,delete, V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array `a` with random values and array `b` to zeros
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copy(a[0:n])
    {
        #pragma acc parallel loop
        for(int x = 0; x < n; ++x){
            a[x] = a[x] * 2; // Modify the array `a` within parallel region
        }

        #pragma acc exit data delete(a[0:n]) // Test delete clause
    }

    // Try accessing `a` after the delete operation to verify if it is inaccessible or unchanged
    for (int x = 0; x < n; ++x){
        b[x] = a[x]; // This should either fail or `a` should remain accessible unchanged post delete. We assume unchanged for validation scenario.
    }

    // Verify if `a` was truly deleted or left unchanged post delete clause usage
    for (int x = 0; x < n; ++x){
        if (b[x] / 2 != rand() / (real_t)(RAND_MAX / 10)){ // Since `a` was supposed to be deleted, checking the condition based on original initialization
            err += 1; // Accumulate errors if any discrepancies found
        }
    }
    
    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}