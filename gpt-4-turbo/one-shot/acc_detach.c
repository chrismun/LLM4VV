#include "acc_testsuite.h"
#ifndef T2
// T2:async,wait,parallel,loop,V:1.0-2.7

// Function to be executed asynchronously
#pragma acc routine
void asyncFunction(real_t* a, real_t* b, int n) {
    #pragma acc loop
    for (int x = 0; x < n; ++x) {
        b[x] = a[x] * 2;
    }
}

int test_acc_detach() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *host_b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        host_b[x] = 0;
    }

    // Perform operations on device
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        // Attach `asyncFunction` to be executed asynchronously on the device
        acc_detach(asyncFunction(a, b, n));
    }

    // Perform similar operation on host for validation
    for (int x = 0; x < n; ++x) {
        host_b[x] = a[x] * 2;
    }
    
    // Validate results
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - host_b[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(host_b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test_acc_detach();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}