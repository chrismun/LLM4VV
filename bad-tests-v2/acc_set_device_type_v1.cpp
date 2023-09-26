#include "acc_testsuite.h"
#include <openacc.h>
#include <iostream>

#ifndef T1
/*T1:acc set device type,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Attempt to set device type to acc_device_nvidia
    acc_set_device_type(acc_device_nvidia);
    
    // Check if the device type was set correctly
    if(acc_get_device_type() != acc_device_nvidia){
        err = 1;
        std::cout << "Failed to set device type to acc_device_nvidia." << std::endl;
    }
    // Attempt to set device type to acc_device_host
    acc_set_device_type(acc_device_host);

    // Check if the device type was set correctly
    if(acc_get_device_type() != acc_device_host){
        err = 1;
        std::cout << "Failed to set device type to acc_device_host." << std::endl;
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