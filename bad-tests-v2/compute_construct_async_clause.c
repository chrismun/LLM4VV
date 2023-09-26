#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Create a device array
    int device_data[100];
    for (int i = 0; i < 100; i++) {
        device_data[i] = i;
    }

    // Create a host array
    int host_data[100];
    for (int i = 0; i < 100; i++) {
        host_data[i] = i;
    }

    // Create a compute construct with the async clause
    #pragma acc compute async(device_data)
    {
        // Perform some computation on the device data
        for (int i = 0; i < 100; i++) {
            device_data[i] += 1;
        }
    }

    // Wait for the computation to complete
    #pragma acc wait

    // Check the results
    for (int i = 0; i < 100; i++) {
        if (device_data[i] != host_data[i] + 1) {
            err = 1;
            break;
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