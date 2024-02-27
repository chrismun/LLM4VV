#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Sample configurations, adjust accordingly.
#define DEVICE_NUMBER 0 // Example device number, may need to adjust based on your setup.
#define DEVICE_TYPE acc_device_nvidia // This could be changed based on the target device type (e.g., acc_device_not_host, acc_device_nvidia, acc_device_radeon, etc.)

int test_acc_set_device_num() {
    int err = 0;

    // Set device number
    acc_set_device_type(DEVICE_TYPE);
    acc_set_device_num(DEVICE_NUMBER, DEVICE_TYPE);

    // Get the current device number
    int current_device = acc_get_device_num(DEVICE_TYPE);

    // Verify if the device set is the same as retrieved
    if (DEVICE_NUMBER != current_device) {
        printf("Error: Mismatch in device numbers. Expected %d, got %d\n", DEVICE_NUMBER, current_device);
        err++;
    } else {
        printf("Test Passed: Correct device number (%d) retrieved.\n", current_device);
    }

    return err;
}

int main() {
    int failcode = 0;
    
    if (test_acc_set_device_num() != 0) {
        failcode = 1;
        printf("Test FAILED.\n");
    } else {
        printf("All tests PASSED.\n");
    }

    return failcode;
}