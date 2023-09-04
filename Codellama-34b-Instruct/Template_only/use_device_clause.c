#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *device_array;
    acc_create_device_array(device_array, 10, 10);

    // Use the device array in a kernel
    #pragma acc parallel loop device(device_array)
    for (int i = 0; i < 10; i++) {
        device_array[i] = i;
    }

    // Verify that the device array is accessible from the host
    for (int i = 0; i < 10; i++) {
        if (device_array[i] != i) {
            err = 1;
            break;
        }
    }

    // Clean up the device array
    acc_delete_device_array(device_array);

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