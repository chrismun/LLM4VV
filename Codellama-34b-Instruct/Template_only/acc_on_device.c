#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    acc_create_device_array(dev_array, 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Copy the device array to the host
    int *host_array = (int *)acc_copy_device_array(dev_array, 10);

    // Verify that the host array contains the same values as the device array
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != dev_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free_device_array(dev_array);

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