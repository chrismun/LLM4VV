#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device memory region
    void *dev_ptr = acc_malloc(1024);
    if (dev_ptr == NULL) {
        fprintf(stderr, "Failed to allocate device memory\n");
        return 1;
    }

    // Map the device memory region to the host
    void *host_ptr = acc_map_data(dev_ptr, 1024);
    if (host_ptr == NULL) {
        fprintf(stderr, "Failed to map device memory to host\n");
        return 1;
    }

    // Unmap the device memory region from the host
    acc_unmap_data(dev_ptr);

    // Check that the device memory region is no longer mapped to the host
    if (acc_is_mapped(dev_ptr)) {
        fprintf(stderr, "Device memory region is still mapped to host after unmap\n");
        return 1;
    }

    // Free the device memory region
    acc_free(dev_ptr);

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