#include <iostream>
#include <openacc.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:acc_async_test,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *host_array = new float[size];
    float *device_array;
    int async_handle = 1; // Using an arbitrary async handle

    // Initialize host array
    for (int i = 0; i < size; ++i) {
        host_array[i] = rand() / (float)RAND_MAX;
    }

    // Allocate memory on the device
    device_array = (float *)acc_malloc(size * sizeof(float));
    if (device_array == NULL) {
        delete[] host_array;
        return 1; // Memory allocation on device failed
    }

    // Copy data to device asynchronously
    #pragma acc enter data copyin(host_array[0:size]) async(async_handle)

    // Test for completion immediately, which should return false as the copy has just started
    if (acc_async_test(async_handle)) {
        err++;
    }

    // Wait for the asynchronous operation to complete
    #pragma acc wait(async_handle)

    // Test again, now should return true as the operation has completed
    if (!acc_async_test(async_handle)) {
        err++;
    }
    
    // Cleanup
    #pragma acc exit data delete(host_array[0:size])
    acc_free(device_array);
    delete[] host_array;

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}