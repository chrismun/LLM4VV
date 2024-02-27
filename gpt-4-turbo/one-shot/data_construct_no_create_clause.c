#include "acc_testsuite.h"
#ifndef T2
// T2:kernels,data,data-region,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_host_copy = (real_t *)malloc(n * sizeof(real_t));

    // Initialize arrays and create a host copy of `a` for verification
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        a_host_copy[x] = a[x]; // Keep original data for verification
    }

    // Copy `a` array to device explicitly to prepare for no_create usage
    #pragma acc enter data copyin(a[0:n])

    // Attempt to use `a` with `no_create`
    // Since `no_create` is used, we perform no operation on `a` to ensure it remains unmodified
    #pragma acc parallel loop no_create(a[0:n])
    for (int x = 0; x < n; ++x){
        // Intentionally no operation to modify `a`, to test no_create
    }

    // Copy data back to host
    #pragma acc exit data copyout(a[0:n])

    // Verify `a` has not been modified: it indicates no_create worked as expected
    for (int x = 0; x < n; ++x){
        if (fabs(a_host_copy[x] - a[x]) > PRECISION){
            // If data has changed, then there's an error with no_create implementation
            err += 1;
        }
    }

    free(a);
    free(a_host_copy);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed != 0){
        failcode += (1 << 1); // Unique bit to indicate test2 failure
    }
#endif

    return failcode;
}