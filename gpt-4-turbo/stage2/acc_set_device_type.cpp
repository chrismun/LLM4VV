#include <openacc.h>
#include <iostream>
#include <cstdlib>

// Defining constants for test. Adjust these as needed.
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1: acc_set_device_type, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Attempt to set device type to acc_device_none first to test if setting device type works
    acc_set_device_type(acc_device_none);

    // Verify that the device type has been set correctly
    if(acc_get_device_type() != acc_device_none) {
        std::cerr << "Error: Device type not set correctly to acc_device_none." << std::endl;
        err++;
    }

    // Attempt to set device type to acc_device_default to test default device setting
    acc_set_device_type(acc_device_default);
    
    // Verify that the device type has been set correctly
    if(acc_get_device_type() != acc_device_default) {
        std::cerr << "Error: Device type not set correctly to acc_device_default." << std::endl;
        err++;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    // Outputting the testing result
    if (failcode == 0) {
        std::cout << "All tests passed successfully." << std::endl;
    } else {
        std::cout << "Some tests failed. Failcode = " << failcode << std::endl;
    }
    return failcode;
}