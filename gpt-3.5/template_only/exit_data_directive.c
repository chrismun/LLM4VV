#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    int n = 100;
    int *host_a, *host_b, *device_a, *device_b;

    host_a = (int*)malloc(n * sizeof(int));
    host_b = (int*)malloc(n * sizeof(int));

    // Initialize host arrays
    for (int i = 0; i < n; i++) {
        host_a[i] = i;
        host_b[i] = 0;
    }

    // Allocate device memory
    device_a = (int*)acc_malloc(n * sizeof(int));
    device_b = (int*)acc_malloc(n * sizeof(int));

    // Copy data from host to device
    #pragma acc enter data copyin(host_a[0:n])
    #pragma acc enter data create(host_b[0:n])

    // Copy data from device to host
    #pragma acc exit data copyout(host_b[0:n])

    // Verify the data on host after exiting data region
    for (int i = 0; i < n; i++) {
        if (host_b[i] != 0) {
            err = 1;
            break;
        }
    }

    // Free device memory
    #pragma acc exit data delete(device_a[0:n])
    #pragma acc exit data delete(device_b[0:n])

    // Free host memory
    free(host_a);
    free(host_b);

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