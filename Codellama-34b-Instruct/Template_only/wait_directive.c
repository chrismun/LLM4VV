#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a device array
    int device_data[10];
    #pragma acc enter data copyin(data)
    #pragma acc enter data copyin(device_data)

    // Launch a kernel to modify the device data
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        device_data[i] = data[i] + 1;
    }

    // Wait for the kernel to complete
    #pragma acc wait

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != data[i] + 1) {
            err = 1;
            break;
        }
    }

    // Clean up
    #pragma acc exit data delete(device_data)
    #pragma acc exit data delete(data)

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