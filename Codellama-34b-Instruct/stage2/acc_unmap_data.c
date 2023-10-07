#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some host memory
    int *host_data = (int *)malloc(sizeof(int) * 10);
    if (host_data == NULL) {
        fprintf(stderr, "Failed to allocate host memory\n");
        return 1;
    }

    // Map the host memory to the device
    int *device_data = (int *)acc_map_data(host_data, sizeof(int) * 10, acc_device_host);
    if (device_data == NULL) {
        fprintf(stderr, "Failed to map host memory to device\n");
        free(host_data);
        return 1;
    }

    // Unmap the device memory from the host
    acc_unmap_data(device_data);

    // Check that the device memory is no longer mapped to the host
    if (acc_is_mapped(device_data)) {
        fprintf(stderr, "Device memory is still mapped to the host after acc_unmap_data\n");
        err = 1;
    }

    // Free the host memory
    free(host_data);

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