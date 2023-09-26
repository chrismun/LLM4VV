#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host pointer to a memory block
    int* host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 1234;

    // Attach the host pointer to the device
    acc_attach(host_ptr);

    // Create a device pointer to the same memory block
    int* device_ptr = (int*)acc_malloc(sizeof(int));

    // Copy the host pointer to the device pointer
    acc_memcpy(device_ptr, host_ptr, sizeof(int));

    // Detach the host pointer from the device
    acc_detach(host_ptr);

    // Check that the device pointer still points to the same memory block
    if (*device_ptr != 1234) {
        err = 1;
    }

    // Free the device memory
    acc_free(device_ptr);

    // Free the host memory
    free(host_ptr);

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