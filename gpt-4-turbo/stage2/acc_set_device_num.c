#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

// Function to test acc_set_device_num
int test_set_device_num(){
    int err = 0;
    int num_devices;
    
    // Select a device type. For simplicity, we use acc_device_default.
    acc_device_t dev_type = acc_device_default;
    
    // First, get the number of devices of the selected type
    num_devices = acc_get_num_devices(dev_type);
    if (num_devices == 0) {
        printf("No devices of the selected type are available.\n");
        return 1; // Error code for no devices available
    }
    
    // For testing, select a device number. Here we use device 0, assuming at least one device is present.
    int dev_num_to_set = 0;
    
    // Attempt to set the device number
    acc_set_device_num(dev_num_to_set, dev_type);

    // Verify if the device number was set correctly
    int current_device = acc_get_device_num(dev_type);
    if (current_device != dev_num_to_set) {
        printf("Device number was not set correctly. Expected %d, got %d.\n", dev_num_to_set, current_device);
        err = 1; // Error code for device number not set correctly
    }
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_set_device_num();
    }
    if (failed != 0){
        failcode += 1; // Signal a failure encountered in the tests
    }

    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    
    return failcode;
}