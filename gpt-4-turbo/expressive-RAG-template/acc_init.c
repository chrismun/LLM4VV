#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Custom test suite header for common definitions and utilities (if necessary).
// This file is assumed to define constants like SEED and NUM_TEST_CALLS.
// For simplicity, we define them directly here if not using a custom header.
#ifndef acc_testsuite_h
#define SEED 12345
#define NUM_TEST_CALLS 10
#endif

#ifndef T1
// T1:acc init,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Attempt to initialize the default device type.
    // The default device is typically acc_device_default or acc_device_nvidia if using NVIDIA GPUs.
    acc_device_t dev_type = acc_get_device_type();
    
    // Try initializing the runtime for the specified device type.
    // This does not specify a device number, so it defaults to device 0 or the system's default.
    // We capture errors by wrapping the call in a try-catch if using C++ or checking error codes in C.
    // OpenACC does not provide direct error return for acc_init, so errors are usually runtime.
    // However, we prepare the err variable for future use or extended checks.
    #pragma acc init device_type(dev_type)

    // Optional: Verify the initialization success indirectly (e.g., querying device count).
    // Note: Direct error checking from acc_init is not provided in the OpenACC API.
    int num_devices = acc_get_num_devices(dev_type);
    if (num_devices <= 0) {
        err = 1; // Indicate an error if no devices are found.
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}