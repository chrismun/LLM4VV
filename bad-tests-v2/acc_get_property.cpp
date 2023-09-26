#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:acc get property,V:2.0-2.7*/
int test1(){
    int err = 0;

    // Get the number of devices of type acc_device_default
    int num_devices = acc_get_num_devices(acc_device_default);
    if(num_devices < 1){
        return 1; // No device found
    }

    // Get the property of the first device
    size_t mem_size = acc_get_property(0, acc_device_default, acc_property_memory);

    // Check if the memory size is returned correctly
    if(mem_size == 0){
        err = 1; // Failed to get the device property
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
    if (failed){
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}