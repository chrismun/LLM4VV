#include <openacc.h>
#include <iostream>

#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;

    // Get the number of devices
    int num_devices = acc_get_num_devices(acc_device_nvidia);
    if(num_devices < 1) {
        std::cerr << "No NVIDIA devices found" << std::endl;
        return 1;
    }

    // Set the device type to NVIDIA
    acc_set_device_type(acc_device_nvidia);

    // Check if the device type is set correctly
    if(acc_get_device_type() != acc_device_nvidia) {
        std::cerr << "Device type not set correctly" << std::endl;
        return 1;
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