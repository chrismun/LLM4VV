#include <iostream>
#include <stdlib.h>
#include <openacc.h>

// Adjust these as necessary for your testing environment
#define SEED 123
#define NUM_TEST_CALLS 10

int test_acc_shutdown(){
    int err = 0;

    // Initialize a variable to use in a data region
    int *host_array = (int *)malloc(10 * sizeof(int));
    int *device_array;

    // Test setup - copy data to device to ensure we have active data on the device
    #pragma acc enter data copyin(host_array[0:10])
    device_array = acc_deviceptr(host_array);

    if(device_array == NULL) {
        std::cerr << "Error during setup: Data not properly mapped to device memory.\n";
        free(host_array);
        return 1; // Fail the test due to setup error
    }

    // Now to test acc_shutdown, we first ensure no kernels are running
    #pragma acc wait

    // Attempt to shutdown all devices of type acc_device_default
    acc_shutdown(acc_device_default);

    // After shutting down, attempting to access device data can lead to undefined behavior.
    // Here, we simply test if acc_shutdown() returns without error.
    // More complex scenarios might require checking the device state or attempting a reinitialization.

    // Cleanup host resources
    free(host_array);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_shutdown();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}