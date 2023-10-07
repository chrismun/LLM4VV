#include <iostream>
#include <cstdlib>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    int* shared_mem = (int*)malloc(sizeof(int));
    *shared_mem = 0;

    // Create a device memory region
    int* device_mem = (int*)malloc(sizeof(int));
    *device_mem = 0;

    // Create a pointer to the shared memory region
    int* shared_ptr = shared_mem;

    // Create a pointer to the device memory region
    int* device_ptr = device_mem;

    // Set the no_create clause on the shared memory region
    #pragma acc data no_create(shared_mem)
    {
        // Increment the shared memory region
        *shared_ptr = *shared_ptr + 1;
    }

    // Set the no_create clause on the device memory region
    #pragma acc data no_create(device_mem)
    {
        // Increment the device memory region
        *device_ptr = *device_ptr + 1;
    }

    // Check the values of the shared and device memory regions
    if (*shared_mem != 1 || *device_mem != 1) {
        err = 1;
    }

    // Free the memory regions
    free(shared_mem);
    free(device_mem);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}