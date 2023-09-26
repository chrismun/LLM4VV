#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        device_array[i] = rand();
    }

    // Update the device array with new values
    for (int i = 0; i < 10; i++) {
        device_array[i] = i * 2;
    }

    // Verify that the device array has been updated correctly
    for (int i = 0; i < 10; i++) {
        if (device_array[i] != i * 2) {
            err = 1;
            break;
        }
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