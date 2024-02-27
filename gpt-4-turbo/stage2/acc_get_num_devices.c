#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h> // Include the OpenACC header

#ifndef T1
// T1:acc_get_num_devices, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test for a default device type, assuming it is supported
    int num_devices_default = acc_get_num_devices(acc_device_default);
    if (num_devices_default <= 0) {
        printf("Test for default device type failed. Expected >0 devices, got %d\n", num_devices_default);
        err++;
    }

    // Test for an unlikely supported device type, assuming none is present
    // Since acc_device_none is undefined in specification, an example invalid type is used as acc_device_host
    // Expectation: should return 0 since it's generally not targeted by OpenACC
    int num_devices_unlikely = acc_get_num_devices(acc_device_host);
    if (num_devices_unlikely != 0) {
        printf("Test for unsupported device type failed. Expected 0 devices, got %d\n", num_devices_unlikely);
        err++;
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