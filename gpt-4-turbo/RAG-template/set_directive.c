#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:{set},V:2.7-3.3
int test1(){
    int err = 0;
    int defaultValue = 0; // Placeholder for implementation-defined initial value.
    int newValue = 1; // Example new value for testing set directive.

    // Testing default_async clause
    #pragma acc set default_async(newValue)
    #pragma acc parallel num_gangs(1)
    {
        // Inside an OpenACC parallel region to make sure the default_async value is set.
    }
    // Reset to the default async queue to verify the effect of the set directive
    acc_set_default_async(defaultValue);
    if(acc_get_default_async() != defaultValue){
        err += 1;
    }
  
    // Testing device_num clause
    newValue = 0; // Assuming 0 is a valid device number for testing.
    #pragma acc set device_num(newValue)
    #pragma acc parallel num_gangs(1)
    {
        // Inside an OpenACC parallel region to make sure the device_num value is set.
    }
    if(acc_get_device_num(acc_get_device_type()) != newValue){
        err += 1;
    }
  
    // Testing device_type clause, assuming device_type of acc_device_default is valid for testing
    int newDeviceType = acc_device_default;
    #pragma acc set device_type(newDeviceType)
    #pragma acc parallel num_gangs(1)
    {
        // Inside an OpenACC parallel region to make sure the device_type value is set.
    }
    if(acc_get_device_type() != newDeviceType){
        err += 1;
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