#include "acc_testsuite.h"

#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device and a queue
    acc_device_t device = acc_get_device(acc_device_default);
    acc_queue_t queue = acc_get_queue(device);

    // Set the device property
    acc_set_property(device, acc_property_device_type, acc_device_type_gpu);

    // Get the device property
    acc_device_type_t device_type = acc_get_property(device, acc_property_device_type);

    // Check if the device property is set correctly
    if (device_type != acc_device_type_gpu) {
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