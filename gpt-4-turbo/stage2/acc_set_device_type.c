#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:acc_set_device_type,V:2.7-3.3
int test1() {
    int err = 0; // Assume no error at the beginning

    // Attempt to set the device type to a GPU, if available
    acc_set_device_type(acc_device_gpu);
    if (acc_get_device_type() != acc_device_gpu) {
        // If after setting, the device type is not GPU, then it's an error
        fprintf(stderr, "Error: acc_set_device_type(acc_device_gpu) failed to set the GPU device.\n");
        err++;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) { // Simplify: Test just once as setting device type is a global action
        failed += test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("Test Passed: acc_set_device_type works correctly.\n");
    } else {
        printf("Test Failed: acc_set_device_type does not work as expected.\n");
    }

    return failcode;
}