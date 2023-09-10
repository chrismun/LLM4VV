#include "openacc.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef T1
int test1(){
    int err = 0;
    int dev_num = 0; // querying the first device
    acc_device_t dev_type = acc_device_nvidia; // assuming the device in testing is an NVIDIA device

    // Query device memory
    size_t device_memory = acc_get_property(dev_num, dev_type, acc_property_memory);
    if(device_memory == 0) { // memory property should not be zero
        err = 1;
        printf("Device memory property query failed\n");
    }

    // Query device name
    const char *device_name = acc_get_property_string(dev_num, dev_type, acc_property_name);
    if(device_name == NULL) { // device name should not be NULL
        err = 1;
        printf("Device name property query failed\n");
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 100; ++x){ // querying 100 times for cost averaging
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}