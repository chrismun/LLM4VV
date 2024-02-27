#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

#define SEED time(NULL)
#define NUM_TEST_CALLS 10

// Test: acc_set_device_num
int test1() {
    int err = 0;
    
    // Initialize random seed
    srand(SEED);
    
    // Initialize device type, assuming the target is a GPU
    acc_device_t dev_type = acc_device_nvidia;
    
    // Get the number of devices of given type
    int num_devices = acc_get_num_devices(dev_type);
    if (num_devices > 0) {
        // Set the device number to a valid device (0 - based index)
        int dev_num = rand() % num_devices; // Pick a random device under the assumption we have more than one
        
        acc_set_device_type(dev_type); // Ensure the device type is set before setting the device number
        acc_set_device_num(dev_num, dev_type);

        // Check if the selected device is set correctly
        int current_device = acc_get_device_num(dev_type);
        if (current_device != dev_num) {
            printf("Error: The current device does not match the expected device. Expected: %d, Got: %d\n", dev_num, current_device);
            err += 1;
        }
    } else {
        printf("No devices of specified type (%d) found. Skipping the test.\n", dev_type);
        // This is not an error in the context of acc_set_device_num,
        // but indicates no device of the requested type is available.
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("Test Passed.\n");
    } else {
        printf("Test Failed with failcode: %d\n", failcode);
    }

    return failcode;
}