#include "acc_testsuite.h"

#ifndef T1
#define T1 1
int test1(){
    int err = 0;
    srand(SEED);

    // Get the number of devices
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    if(num_devices < 1){
        printf("No NVIDIA devices found\n");
        return 1;
    }

    // Get the device number
    int device_num = acc_get_device_num(acc_device_nvidia);
    if(device_num < 0){
        printf("Failed to get device number\n");
        return 1;
    }

    // Shutdown the device
    acc_shutdown(acc_device_nvidia);

    // Check if the device is still available
    acc_device_t device_type = acc_get_device_type(device_num);
    if(device_type == acc_device_nvidia){
        printf("Device is still available after shutdown\n");
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failcode = failcode + test1();
    }
#endif
    return failcode;
}