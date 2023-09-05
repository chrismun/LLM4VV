#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

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

void acc_shutdown(acc_device_t dev_type){
    // Shut down the connection to the specified device
    acc_device_t device = acc_get_device(dev_type);
    if (device == NULL) {
        // Device not found
        return;
    }
    acc_shutdown_device(device);
}

void acc_shutdown_device(int dev_num, acc_device_t dev_type){
    // Shut down the connection to the specified device
    acc_device_t device = acc_get_device(dev_type);
    if (device == NULL) {
        // Device not found
        return;
    }
    if (dev_num < 0 || dev_num >= device->num_devices) {
        // Invalid device number
        return;
    }
    acc_shutdown_device(device->devices[dev_num]);
}