#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *host_arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i) {
        host_arr[i] = rand() % 100; // Initialize the host array with random values.
    }

    // Copy host array to device and create space for it there.
#pragma acc enter data copyin(host_arr[0:size])

    // Modify the array in device memory.
#pragma acc parallel loop present(host_arr[0:size])
    for (int i = 0; i < size; ++i) {
        host_arr[i] += 1; // Increment each element to verify the data was modified on the device.
    }

    // Copy modified array back to the host.
#pragma acc update host(host_arr[0:size])

    // Verify modifications.
    for (int i = 0; i < size; ++i) {
        if (host_arr[i] % 100 == 0) { // Check if addition made in the device is reflected on the host.
            err += 1;
        }
    }

    // Cleanup
#pragma acc exit data delete(host_arr[0:size])
    free(host_arr);

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