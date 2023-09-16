#include "openacc.h"
#include "acc_testsuite.h"

// Global properties
acc_device_t devType;
acc_device_t devType_current;
int numDevices;
int numDevices_current;

int test1(){
    int err = 0;

    //Get the number of devices
    numDevices = acc_get_num_devices( devType );

    // Make sure there is at least one device
    if(numDevices < 1){
        return 1;
    }

    //Get the current device type
    devType_current = acc_get_device_type();

    // Test if get property works
    if( devType_current != devType ) {
        return 1;
    }

    //Get the current num of devices
    numDevices_current = acc_get_num_devices( devType_current );

    // Test if get property works
    if( numDevices_current != numDevices ) {
        return 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    devType = acc_device_nvidia; // Set your required device type here

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}