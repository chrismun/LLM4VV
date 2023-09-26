#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Declare variables and allocate memory on host
    int* a = (int*)malloc(N * sizeof(int));
    int* b = (int*)malloc(N * sizeof(int));

    // Initialize data on host
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 10;
        b[i] = 0;
    }

    // Transfer data from host to device
    #pragma acc data copyin(a[0:N]) create(b[0:N])
    {
        // Perform computation on device
        #pragma acc parallel loop present(a[0:N], b[0:N])
        for (int i = 0; i < N; i++) {
            // Store result on device
            b[i] = a[i] * a[i];
        }
    }

    // Transfer data from device to host
    #pragma acc data copyout(b[0:N]) delete(a[0:N])

    // Verify the results
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i] * a[i]) {
            err = 1;
            break;
        }
    }

    // Free memory on host
    free(a);
    free(b);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}