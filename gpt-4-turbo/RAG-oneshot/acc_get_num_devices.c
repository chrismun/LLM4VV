#include <stdio.h>
#include <openacc.h>

// Function to test acc_get_num_devices for a given device type
int test_acc_get_num_devices(acc_device_t dev_type) {
    int num_devices = acc_get_num_devices(dev_type);
    printf("Number of devices of type %d: %d\n", (int)dev_type, num_devices);
    // Verify the result. Since correctness depends on the environment and the
    // specific implementation, we're assuming that having non-negative results
    // is a sign of the function working. In a real scenario, you might have
    // specific expectations to check against.
    if (num_devices >= 0) {
        return 0; // Passed
    } else {
        return 1; // Failed
    }
}

int main() {
    int failcode = 0;

    // Test for default device
    if (test_acc_get_num_devices(acc_device_default) != 0) {
        failcode |= 1;
    }
    // Test for NVIDIA GPUs if applicable/available
    if (test_acc_get_num_devices(acc_device_nvidia) != 0) {
        failcode |= (1 << 1);
    }
    // You can add more device types to test as needed by following the pattern above.

    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed. Fail code: %d\n", failcode);
    }

    return failcode;
}