#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array on the device
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the array on the device
    for (int i = 0; i < 10; i++) {
        device_array[i] = i;
    }

    // Declare the array as a device array
    acc_declare_device_array(device_array, 10);

    // Verify that the array is on the device
    if (acc_is_device_array(device_array) != 1) {
        err = 1;
    }

    // Free the device array
    acc_free(device_array);

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