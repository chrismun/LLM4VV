#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host pointer to a device buffer
    int *host_ptr = (int *)malloc(sizeof(int) * 10);
    int *device_ptr = (int *)malloc(sizeof(int) * 10);

    // Initialize the host and device buffers
    for (int i = 0; i < 10; i++) {
        host_ptr[i] = i;
        device_ptr[i] = i;
    }

    // Map the host buffer to the device buffer
    #pragma acc enter data create(host_ptr[0:10])
    #pragma acc enter data copyin(device_ptr[0:10])

    // Unmap the host buffer from the device buffer
    #pragma acc unmap(host_ptr)

    // Check if the host buffer is still accessible
    for (int i = 0; i < 10; i++) {
        if (host_ptr[i] != i) {
            err = 1;
            break;
        }
    }

    // Clean up
    free(host_ptr);
    free(device_ptr);

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