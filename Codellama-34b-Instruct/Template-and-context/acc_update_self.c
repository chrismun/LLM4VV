#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    void *shared_mem = acc_malloc(1024);
    if (shared_mem == NULL) {
        printf("Failed to allocate shared memory\n");
        return 1;
    }

    // Create a device memory region
    void *device_mem = acc_malloc(1024);
    if (device_mem == NULL) {
        printf("Failed to allocate device memory\n");
        return 1;
    }

    // Initialize the shared memory region
    memset(shared_mem, 0, 1024);

    // Initialize the device memory region
    memset(device_mem, 0, 1024);

    // Update the device memory region from the shared memory region
    acc_update_self(shared_mem, 1024);

    // Check that the device memory region has been updated
    if (memcmp(device_mem, shared_mem, 1024) != 0) {
        printf("Device memory region has not been updated\n");
        err = 1;
    }

    // Free the device memory region
    acc_free(device_mem);

    // Free the shared memory region
    acc_free(shared_mem);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}