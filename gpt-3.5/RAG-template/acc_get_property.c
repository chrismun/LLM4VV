#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;

    // Call acc_get_property to get the size of device memory
    size_t memory_size = acc_get_property(0, acc_device_nvidia, acc_property_memory);
    if (memory_size == 0){
        err = 1;
    }

    // Call acc_get_property_string to get the device name
    const char* device_name = acc_get_property_string(0, acc_device_nvidia, acc_property_name);
    if (device_name == NULL){
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