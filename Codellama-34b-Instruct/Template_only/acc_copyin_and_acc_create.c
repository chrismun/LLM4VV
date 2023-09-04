#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array on the device
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Copy data from the host to the device
    acc_copyin(device_array, host_array, sizeof(int) * 10);

    // Create a new array on the device and copy data from the host to it
    int *device_array2 = (int *)acc_malloc(sizeof(int) * 10);
    acc_copyin(device_array2, host_array2, sizeof(int) * 10);

    // Verify that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (device_array[i] != host_array[i]) {
            err = 1;
            break;
        }
    }

    // Verify that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (device_array2[i] != host_array2[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    acc_free(device_array);
    acc_free(device_array2);

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