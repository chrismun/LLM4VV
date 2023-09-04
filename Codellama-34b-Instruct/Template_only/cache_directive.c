#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int *arr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand();
    }

    // Create a device array and copy the host array to it
    int *dev_arr;
    acc_create(&dev_arr, arr, sizeof(int) * 10);

    // Create a cache directive for the device array
    acc_cache(dev_arr, sizeof(int) * 10, ACC_CACHE_READ_WRITE);

    // Modify the device array
    for (int i = 0; i < 10; i++) {
        dev_arr[i] = dev_arr[i] + 1;
    }

    // Synchronize the device array with the host array
    acc_sync(dev_arr, sizeof(int) * 10, ACC_SYNC_READ_WRITE);

    // Check if the host array has been modified
    for (int i = 0; i < 10; i++) {
        if (arr[i] != dev_arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free(dev_arr);

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