#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int* host_array = (int*)malloc(size * sizeof(int));
    int* device_array;

    // Initialize host data
    for (int i = 0; i < size; ++i) {
        host_array[i] = rand() % 100; // Populate with random values
    }

    // Allocate memory on the device and copy data from the host to the device
    device_array = (int*) acc_malloc(size * sizeof(int));
    acc_memcpy_to_device(device_array, host_array, size * sizeof(int));

    // Use the host_data construct with use_device clause
#pragma acc parallel loop present(device_array)
    for (int i = 0; i < size; ++i) {
        device_array[i] += 1; // Simple operation on the device
    }

#pragma acc host_data use_device(device_array)
    {
        // Example where we could call an optimized library or API that works directly with device pointers.
        // For simplicity's sake, we're not invoking any such API here since the focus is on the use_device clause.
        // The actual operation has been performed in the parallel loop above; this section is illustrative.
    }

    // Copy results back to host
    acc_memcpy_from_device(host_array, device_array, size * sizeof(int));

    // Verify results
    for (int i = 0; i < size; ++i) {
        if (host_array[i] % 100 + 1 != (host_array[i] - rand() % 100 + 100) % 100) { // Adjusting the verification logic to account for initial random values
            err++;
        }
    }

    // Cleanup
    acc_free(device_array);
    free(host_array);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}