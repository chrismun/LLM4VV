#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t * a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * a_device = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array on host
    for (int x = 0; x < n; ++x) {
        a_host[x] = rand() / (real_t)(RAND_MAX / 10);
        a_device[x] = 0;
    }

    // Copy data to device and apply computation
    #pragma acc data copy(a_device[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x) {
            a_device[x] = a_host[x] * 2; // Example computation
        }
        // Update the host with the computed results on the device
        #pragma acc update self(a_device[0:n])
    }

    // Verify the correctness of the operation
    for (int x = 0; x < n; ++x) {
        if (fabs(a_device[x] - (a_host[x] * 2)) > PRECISION) {
            err += 1;
        }
    }

    free(a_host);
    free(a_device);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode |= 1; // Set the failure bit for test 1
    }
#endif

    return failcode;
}