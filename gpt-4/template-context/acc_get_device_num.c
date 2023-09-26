#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1() {
    int current_device_num;

    // Initialize the device, this should also set the current device number
    acc_init(acc_device_default);

    current_device_num = acc_get_device_num(acc_device_default);

    // if there is no device or the device is not supported, the function will return -1
    // So if current_device_num is -1, it means the function is not working well
    if(current_device_num == -1) {
        printf("Test failed: No device found or device not supported.\n");
        return 1; // 1 for error
    }

    printf("Test passed: Current device number is %d.\n", current_device_num);

    return 0; // 0 for no error
}
#endif

int main(){
    int failcode = 0;

#ifndef T1
    failcode = test1();
#endif

    return failcode;
}