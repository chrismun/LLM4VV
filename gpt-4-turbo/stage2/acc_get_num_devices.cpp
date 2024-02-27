#include <openacc.h>
#include <iostream>
#include <cstdlib>

// The given acc_testsuite.h file is not provided, assuming it defines SEED and NUM_TEST_CALLS
// For simplicity, we define them here if not already defined.
#ifndef acc_testsuite_h
#define SEED 123
#define NUM_TEST_CALLS 10
#endif

// Test for acc_get_num_devices function
int test1() {
    int err = 0; // No error initially
    srand(SEED);

    // Test different device types defined by OpenACC
    acc_device_t device_types[] = {
        acc_device_none,
        acc_device_default,
        acc_device_host,
        acc_device_not_host,
    };

    int num_device_types = sizeof(device_types) / sizeof(acc_device_t);

    // Checking the number of devices for each device type
    for(int i = 0; i < num_device_types; ++i) {
        int num_devices = acc_get_num_devices(device_types[i]);
        std::cout << "Number of devices for device type " << device_types[i] << ": " << num_devices << std::endl;

        // Since the behavior might vary depending on the system and setup, 
        // we simply check if the function returns a non-negative number as a basic test.
        if(num_devices < 0) {
            std::cerr << "Error: acc_get_num_devices returned a negative value for device type " << device_types[i] << std::endl;
            err += 1; // Increment error count
        }
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