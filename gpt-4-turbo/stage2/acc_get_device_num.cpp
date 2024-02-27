#include <openacc.h>
#include <cstdlib>
#include <iostream>

// Define these if they're not provided by the testing environment
#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test function testing acc_get_device_num
int test1() {
    int err = 0;
    srand(SEED);

    // Test with a generally supported device type, assuming GPUs are available
    int gpu_device_num = acc_get_device_num(acc_device_nvidia);
    if (gpu_device_num < 0) {
        // We expect to get a valid device number if GPUs are available
        std::cerr << "Expected a valid GPU device number, but got " << gpu_device_num << std::endl;
        err += 1;
    }

    // Test with an unsupported device type
    int invalid_device_num = acc_get_device_num(static_cast<acc_device_t>(9999)); // Assuming 9999 is not a valid device type
    if (invalid_device_num != -1) {
        // We expect to get -1 for an unsupported device type
        std::cerr << "Expected -1 for an unsupported device type, but got " << invalid_device_num << std::endl;
        err += 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    return failcode;
}