#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;

    // Get the number of devices of type acc_device_host
    int num_devices = acc_get_device_num(acc_device_host);
    if (num_devices < 0) {
        printf("Error: No devices of type acc_device_host\n");
        err = 1;
    } else {
        printf("Number of devices of type acc_device_host: %d\n", num_devices);
    }

    // Get the number of devices of type acc_device_not_host
    num_devices = acc_get_device_num(acc_device_not_host);
    if (num_devices < 0) {
        printf("Error: No devices of type acc_device_not_host\n");
        err = 1;
    } else {
        printf("Number of devices of type acc_device_not_host: %d\n", num_devices);
    }

    // Get the number of devices of type acc_device_nvidia
    num_devices = acc_get_device_num(acc_device_nvidia);
    if (num_devices < 0) {
        printf("Error: No devices of type acc_device_nvidia\n");
        err = 1;
    } else {
        printf("Number of devices of type acc_device_nvidia: %d\n", num_devices);
    }

    // Get the number of devices of type acc_device_radeon
    num_devices = acc_get_device_num(acc_device_radeon);
    if (num_devices < 0) {
        printf("Error: No devices of type acc_device_radeon\n");
        err = 1;
    } else {
        printf("Number of devices of type acc_device_radeon: %d\n", num_devices);
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}