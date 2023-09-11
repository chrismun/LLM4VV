#include <iostream>
#include <cstdlib>
#include <cstring>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some memory on the device
    void* data_dev = malloc(1024);
    if (data_dev == NULL) {
        std::cerr << "Failed to allocate memory on device" << std::endl;
        return 1;
    }

    // Map the device memory to a host address
    void* data_arg = acc_map_data(data_dev, 1024);
    if (data_arg == NULL) {
        std::cerr << "Failed to map device memory to host address" << std::endl;
        return 1;
    }

    // Use the mapped memory
    memset(data_arg, 0, 1024);

    // Unmap the memory
    acc_unmap_data(data_arg);

    // Free the device memory
    free(data_dev);

    return 0;
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