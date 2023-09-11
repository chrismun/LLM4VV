#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some memory on the host
    void *host_data = malloc(1024);
    if (host_data == NULL) {
        fprintf(stderr, "Failed to allocate memory on the host\n");
        return 1;
    }

    // Allocate some memory on the device
    void *device_data = acc_malloc(1024);
    if (device_data == NULL) {
        fprintf(stderr, "Failed to allocate memory on the device\n");
        return 1;
    }

    // Map the device memory to the host memory
    acc_map_data(host_data, device_data, 1024);

    // Check that the data is correctly mapped
    if (memcmp(host_data, device_data, 1024) != 0) {
        fprintf(stderr, "Data is not correctly mapped\n");
        err = 1;
    }

    // Unmap the device memory
    acc_unmap_data(host_data);

    // Free the memory on the host and device
    free(host_data);
    acc_free(device_data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}