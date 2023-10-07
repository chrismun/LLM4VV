#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the host data
    int host_data[10];
    for (int i = 0; i < 10; i++) {
        host_data[i] = i;
    }

    // Create a device data array
    int device_data[10];

    // Use the host_data construct with an if clause to copy the data to the device
    #pragma acc host_data if(host_data[0] == 0)
    {
        // Copy the data to the device
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Check that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != host_data[i]) {
            err++;
        }
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