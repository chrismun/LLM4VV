#include <stdlib.h>
#include <stdio.h>
#include "openacc.h" // Ensure this is included for OpenACC API

#ifndef T1
//T1:acc_get_device_type,V:2.7-3.3
int test1(){
    int err = 0;

    // Getting the device type - as per the OpenACC specification.
    acc_device_t device_type = acc_get_device_type();

    // The specification mentions that if the device type has not yet been selected,
    // acc_device_none may be returned. So, we check against known device types also.
    if (device_type != acc_device_none && device_type != acc_device_nvidia && device_type != acc_device_radeon && device_type != acc_device_xeonphi && device_type != acc_device_gpu && device_type != acc_device_default) {
        // If the value returned does not match any known device or acc_device_none, consider it an error.
        printf("Error: acc_get_device_type returned an unexpected value.\n");
        err = 1;
    } else {
        // For demonstration purposes, let's print the device type returned
        printf("Device type detected successfully: %d\n", (int)device_type);
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < 1; ++x){  // Assuming a simpler single call for demonstration, replace with NUM_TEST_CALLS for multiple iterations if defined
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
      printf("Test passed successfully.\n");
    } else {
      printf("Test failed.\n");
    }
    return failcode;
}