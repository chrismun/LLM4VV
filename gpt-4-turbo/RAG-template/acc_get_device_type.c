#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Using acc_get_device_type to check the current device type.
    acc_device_t device_type = acc_get_device_type();

    // Check if the device type is one of the known types or acc_device_none.
    switch(device_type) {
        case acc_device_none:
            // No device selected yet is a valid case, but we print it for information.
            printf("No device has been selected yet.\n");
            break;
        case acc_device_default:
        case acc_device_host:
        case acc_device_not_host:
        case acc_device_nvidia:
        case acc_device_radeon:
        case acc_device_xeonphi:
        case acc_device_gpu:
        case acc_device_current:
            // These are valid device types according to the specification.
            break;
        default:
            // If the device type is none of the above, it's an error.
            printf("Unknown device type returned: %d\n", device_type);
            err++;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if(failcode) {
        printf("Test failed with error code %d\n", failcode);
    } else {
        printf("All tests passed successfully.\n");
    }
    return failcode;
}