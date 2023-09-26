#include <iostream>
#include <cstdlib>
#include <cstring>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some host memory
    int* host_data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_data[i] = i;
    }

    // Map the host memory to the device
    int* device_data = (int*)acc_map_data(host_data, sizeof(int) * 10);

    // Unmap the device memory
    acc_unmap_data(device_data);

    // Check that the device memory is no longer mapped
    if (acc_is_mapped(device_data)) {
        std::cerr << "Error: device memory is still mapped after acc_unmap_data" << std::endl;
        err = 1;
    }

    // Free the host memory
    free(host_data);

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