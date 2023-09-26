#include "acc_testsuite.h"
#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

int test_device_properties(){
    const acc_device_t device_type = acc_device_nvidia; // Or any other device type.
    const int device_number = 0; // Let's check for the first device.

    // Verify memory property
    size_t total_memory = acc_get_property(device_number, device_type, acc_property_memory);
    if (total_memory == 0){
        fprintf(stderr, "Error: Total Memory is zero on the device or unable to get the memory value.\n");
        return 1;
    }

    // Verify name  
    const char* device_name = acc_get_property_string(device_number, device_type, acc_property_name);
    if (device_name == NULL){
        fprintf(stderr, "Error: No device name returned.\n");
        return 1;
    }
  
    return 0; // No errors.
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = test_device_properties(); 
    failcode = failed ? failcode + 1 : failcode;
    if(failcode != 0){
        fprintf(stderr, "Error: OpenACC device property test failed! \n");
    }

    return failcode;
}