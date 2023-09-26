#include <iostream>
#include <cstdlib>
#include <cstring>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Create a pointer to a shared memory region
    int* shared_memory = (int*)malloc(sizeof(int));

    // Create a pointer to a device memory region
    int* device_memory = (int*)malloc(sizeof(int));

    // Initialize the shared memory region
    *shared_memory = 1234;

    // Initialize the device memory region
    *device_memory = 5678;

    // Create a data present clause
    #pragma acc data present(shared_memory)
    {
        // Attach the shared memory region to the device
        #pragma acc attach(shared_memory)

        // Detach the shared memory region from the device
        #pragma acc detach(shared_memory)
    }

    // Check if the shared memory region is still present in the device memory
    if (*shared_memory != 1234) {
        err = 1;
    }

    // Check if the device memory region is still present in the device memory
    if (*device_memory != 5678) {
        err = 1;
    }

    // Free the memory regions
    free(shared_memory);
    free(device_memory);

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