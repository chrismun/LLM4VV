#include <iostream>
#include <cstdlib>
#include <cstring>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host array
    int* host_array = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Create a device pointer
    int* device_ptr = (int*)acc_deviceptr(host_array);

    // Check that the device pointer is not null
    if (device_ptr == nullptr) {
        std::cout << "Device pointer is null" << std::endl;
        err = 1;
    }

    // Check that the device pointer points to the correct location
    if (device_ptr != host_array) {
        std::cout << "Device pointer does not point to the correct location" << std::endl;
        err = 1;
    }

    // Free the host array
    free(host_array);

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