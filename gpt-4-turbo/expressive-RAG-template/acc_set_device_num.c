#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// Test for acc_set_device_num, Version: 2.7-3.3
int test1() {
    int err = 0;
    srand(time(NULL));

    // Assuming to test for a GPU device type
    acc_device_t dev_type = acc_device_nvidia; // Change this based on available device types
    int num_devices = acc_get_num_devices(dev_type);

    if (num_devices > 0) {
        int selected_device = rand() % num_devices; // Select a random device

        acc_set_device_type(dev_type); // Set the device type
        acc_set_device_num(selected_device, dev_type); // Set the device number

        int current_device = acc_get_device_num(dev_type);

        if (current_device != selected_device) {
            printf("Error: Device number not set correctly. Expected %d, Got %d\n", selected_device, current_device);
            err = 1;
        }
    } else {
        printf("No devices of the specified type (%d) are available.\n", dev_type);
        err = 1;
    }

    // Test with an invalid device number to see if it handles the error.
    acc_set_device_num(-1, dev_type);
    if (acc_get_device_num(dev_type) != 0) { // Assuming the default device is 0
        printf("Error handling with invalid device number not working as expected.\n");
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 1; ++x) { // Assuming a single test call, adjust NUM_TEST_CALLS as needed
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    return failcode;
}