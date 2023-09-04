#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    void *shared_mem = acc_malloc(1024);
    if (shared_mem == NULL) {
        err = 1;
        goto cleanup;
    }

    // Create a device memory region
    void *device_mem = acc_malloc(1024);
    if (device_mem == NULL) {
        err = 1;
        goto cleanup;
    }

    // Initialize the shared memory region
    memset(shared_mem, 0, 1024);

    // Update the device memory region from the shared memory region
    acc_update_device(shared_mem, 1024);

    // Check that the device memory region has been updated
    if (memcmp(device_mem, shared_mem, 1024) != 0) {
        err = 1;
        goto cleanup;
    }

    // Update the shared memory region from the device memory region
    acc_update_self(device_mem, 1024);

    // Check that the shared memory region has been updated
    if (memcmp(shared_mem, device_mem, 1024) != 0) {
        err = 1;
        goto cleanup;
    }

cleanup:
    acc_free(shared_mem);
    acc_free(device_mem);
    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}