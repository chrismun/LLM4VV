#include "acc_testsuite.h"
#ifndef T1
// T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Test setup: Ensure an OpenACC device is available
    if (acc_get_num_devices(acc_device_none) == 0) {
        printf("No OpenACC devices available.\n");
        return 1; // Indicating an error since no device can be tested
    }

    // Initialize OpenACC device
    acc_init(acc_device_default);
    int default_device = acc_get_device_type();

    // Test: Attempt to get the device number for the current device
    int device_num = acc_get_device_num(default_device);
    if (device_num < 0){
        printf("Error: Invalid device number returned.\n");
        err = 1;
    } else {
        // Optionally print the device number, can be commented out.
        printf("Current OpenACC device number: %d\n", device_num);
    }

    acc_shutdown(acc_device_default);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}