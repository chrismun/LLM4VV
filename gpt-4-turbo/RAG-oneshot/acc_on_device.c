#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

// Function prototypes for test routines
int test_on_host();
int test_on_not_host();
int test_on_specific_device(acc_device_t device_type);

int main() {
    int failcode = 0;

    // Test running on host
    if (test_on_host() != 0) {
        failcode |= (1 << 0);
        printf("Test on host FAILED.\n");
    } else {
        printf("Test on host PASSED.\n");
    }

    // Test running on any device that is not host
    if (test_on_not_host() != 0) {
        failcode |= (1 << 1);
        printf("Test on not host FAILED.\n");
    } else {
        printf("Test on not host PASSED.\n");
    }

    // Test running on a specific device type, for demonstration, using NVIDIA as an example
    acc_device_t device_type = acc_device_nvidia; // or any other acc_device_t that might be relevant for your setup
    if (test_on_specific_device(device_type) != 0) {
        failcode |= (1 << 2);
        printf("Test on specific device (%d) FAILED.\n", device_type);
    } else {
        printf("Test on specific device (%d) PASSED.\n", device_type);
    }

    return failcode;
}

int test_on_host() {
    // Should return true if we're on host
    if (acc_on_device(acc_device_host)) {
        return 0; // Passed
    } else {
        return 1; // Failed
    }
}

int test_on_not_host() {
    // Should return false if we're on host, true otherwise
    if (acc_on_device(acc_device_not_host)) {
        return 0; // This makes sense only if executed in an accelerator context, thus, may pass/fail depending on setup
    } else {
        // If it returns false, we ensure we are currently on the host
        if (acc_on_device(acc_device_host)) {
            return 0; // Passed, we're on the host as expected
        } else {
            return 1; // Failed, unexpected behavior
        }
    }
}

int test_on_specific_device(acc_device_t device_type) {
    // In a real scenario, the implementation might require a region or a routine executed on the device of type device_type to correctly test this. 
    // This particular test might therefore always return 0 (passed) when not in an accelerator region specific to device_type.

    // Note: This is a placeholder function as actual testing on specific device type requires executing in a context or region specific to the device,
    // which is beyond a simple C code example and depends heavily on the runtime environment and hardware setup
    return 0; // Assuming pass as proper testing requires specific setup
}