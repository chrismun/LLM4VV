#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Testing for different device types
    acc_device_t device_types[] = {acc_device_none, acc_device_default, acc_device_host, acc_device_not_host, acc_device_nvidia, acc_device_radeon, acc_device_gpu};
    int num_device_types = sizeof(device_types) / sizeof(acc_device_t);

    for (int i = 0; i < num_device_types; ++i) {
        int num_devices = acc_get_num_devices(device_types[i]);
        if (device_types[i] == acc_device_none) {
            // acc_device_none is not a valid device, so it should return 0
            if (num_devices != 0) {
                printf("Error: acc_get_num_devices(acc_device_none) != 0\n");
                err++;
            }
        } else {
            // For all valid device types, ensure it does not return a negative value
            if (num_devices < 0) {
                printf("Error: acc_get_num_devices returned a negative value for device type %d\n", device_types[i]);
                err++;
            }
        }
        // Note: Without knowing the actual setup/environment, where there could be no devices,
        // or more than one of a particular type, we should not assume any specific positive number
        // of devices and thus cannot further validate the specific count beyond >= 0 for valid types.
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}