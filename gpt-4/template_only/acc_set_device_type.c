#include "openacc.h"
#include "acc_testsuite.h"

#ifndef T1
int testAccSetDeviceType(){
    int err = 0; 
    int deviceTypeSet = 0;
    int deviceTypeGet = 0;
    
    acc_set_device_type(acc_device_nvidia); // Specify the device type
    deviceTypeSet = acc_device_nvidia;
    
    deviceTypeGet = acc_get_device_type(); // Retrieve the device type
    
    if(deviceTypeSet != deviceTypeGet){
        err = 1; 
    }
    return err;
}
#endif

int main(){
    int failcode = 0;
    int hasFailed;
#ifndef T1
    hasFailed = testAccSetDeviceType();  // Invoke the test

    if (hasFailed){
        failcode = failcode + 1;
    }
#endif
    return failcode;
}