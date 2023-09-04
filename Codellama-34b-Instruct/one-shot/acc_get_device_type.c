#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main(){
    int failcode = 0;
    int failed;

    // Initialize OpenACC
    acc_init(acc_device_default);

    // Allocate memory for device type
    acc_device_t device_type;

    // Get device type
    acc_get_device_type(&device_type);

    // Check if device type is supported
    if (device_type == acc_device_none){
        printf("Device type not supported\n");
        failcode = 1;
    }

    // Cleanup OpenACC
    acc_shutdown(acc_device_default);

    return failcode;
}