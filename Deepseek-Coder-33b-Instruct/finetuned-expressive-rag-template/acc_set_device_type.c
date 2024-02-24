#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define T1
#define SEED 1234
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Get the number of devices
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    if(num_devices < 1){
        printf("No NVIDIA devices found\n");
        return 1;
    }

    // Set the device type to the first available device
    acc_set_device_type(acc_device_nvidia);

    // Check if the device type is set correctly
    if(acc_get_device_type() != acc_device_nvidia){
        printf("Device type not set correctly\n");
        return 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
#ifdef T1
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