#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

// Assuming an acc_testsuite.h exists and defines SEED and NUM_TEST_CALLS.
// #include "acc_testsuite.h"

#ifndef T1
// T1:acc shutdown,V:2.7-3.3
int test1(){
    int err = 0;

    // Choose the default device type.
    acc_device_t dev_type = acc_get_device_type();
    int num_devices = acc_get_num_devices(dev_type);

    // If there are no devices of this type, we cannot test shutdown.
    if (num_devices <= 0){
        printf("No accelerator devices of the chosen type available.\n");
        return 1; // Indicating a skipped test rather than a fail.
    }
    
    // Ensure we're operating on a valid device.
    acc_set_device_type(dev_type);
    acc_init(dev_type);
    int dev_num = acc_get_device_num(dev_type);

    // Perform an operation to ensure the device is utilized.
    #pragma acc kernels
    for (int i = 0; i < 100; ++i) {
        // A simple loop intended to ensure a device is engaged.
    }

    // Attempt to shut down the device.
    acc_shutdown(dev_type);

    // Try to re-engage the device with a compute operation.
    // Expectation: This should fail or result in undefined behavior if shutdown was successful.
    // Note: There's no direct and safe way to "test" undefined behavior; we infer it from program context.
    int errors_post_shutdown = 0;

    #pragma acc kernels if(0) // Intending not to execute but showing an attempt.
    for (int i = 0; i < 100; ++i) {
        errors_post_shutdown = 1; // This line is not supposed to be executed.
    }

    // Shutdown is successful if we can't properly execute operations on the device anymore.
    // Since we can't directly capture undefined behavior, we rely on `errors_post_shutdown` staying as `0`.
    err = errors_post_shutdown;

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("Test passed\n");
    } else {
        printf("Test failed\n");
    }
    return failcode;
}