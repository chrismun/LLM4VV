#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    int host_a[NUM_ELEMS];
    int *device_a;

    srand(SEED);

#pragma acc data copyin(host_a[0:NUM_ELEMS])
    {
        // Allocate device memory
        device_a = (int *)acc_malloc(NUM_ELEMS * sizeof(int));

        // Initialize host array
        for (int i = 0; i < NUM_ELEMS; i++) {
            host_a[i] = rand();
        }

        // Copy host data to device
        #pragma acc update device(host_a[0:NUM_ELEMS])

        // Perform device computations
        #pragma acc parallel loop
        for (int i = 0; i < NUM_ELEMS; i++) {
            device_a[i] = host_a[i] + 1;
        }

        // Copy device data back to host
        #pragma acc update self(host_a[0:NUM_ELEMS])

        // Verify the results
        for (int i = 0; i < NUM_ELEMS; i++) {
            if (host_a[i] != (device_a[i] - 1)) {
                err = 1;
                break;
            }
        }

        // Deallocate device memory
        acc_free(device_a);
    }

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