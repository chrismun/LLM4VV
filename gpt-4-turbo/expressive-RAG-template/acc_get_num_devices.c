#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Test function declaration
int test_acc_get_num_devices();

int main() {
    int failcode = 0;
    int failed = 0;

    // Run the test multiple times to check consistency
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_get_num_devices();
    }

    if (failed != 0) {
        failcode = 1; // Using a simple fail code schema
    }

    return failcode;
}

// Testing acc_get_num_devices functionality
int test_acc_get_num_devices() {
    int err = 0;

    // Initialize srand for any potential usage
    srand(SEED);

    // Use acc_get_num_devices to get the number of default devices
    int num_devices = acc_get_num_devices(acc_device_default);

    // Depending on the implementation, if no default devices are available or not supported, zero is returned
    // Ideally, there should be at least one device (the host device) in most environments
    if(num_devices <= 0) {
        printf("No default device types available or supported.\n");
        err += 1; // Increment error count
    } else {
        printf("Number of default devices available: %d\n", num_devices);
    }

    return err;
}