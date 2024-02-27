#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include <time.h>

#ifndef T1
// T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;

    // Initialize random number generator for potential random device selection
    srand((unsigned int)time(NULL));

    // Attempt to set a device number. For simplicity, use device number 0 and acc_device_nvidia (or any other device type you expect to be available on your system)
    int devNum = 0; // Generally, 0 is a safe choice assuming at least one device is present
    acc_device_t devType = acc_device_nvidia; // Change this as per available device types on your system

    // Set the device number
    acc_set_device_num(devNum, devType);

    // Verify if the device was set
    if(acc_get_device_type() != devType || acc_get_device_num(devType) != devNum) {
        printf("Error: Device type or number doesn't match.\n");
        err = 1; // Error encountered
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASS: The acc_set_device_num functionality verification succeeded.\n");
    } else {
        printf("FAIL: The acc_set_device_num functionality verification failed.\n");
    }
    return failcode;
}