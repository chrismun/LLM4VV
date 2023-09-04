#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a copy of the array on the device
    int* dev_arr = (int*)acc_malloc(sizeof(int) * 10);
    acc_memcpy(dev_arr, arr, sizeof(int) * 10);

    // Modify the array on the device
    for (int i = 0; i < 10; i++) {
        dev_arr[i] = dev_arr[i] + 1;
    }

    // Copy the modified array back to the host
    acc_memcpy(arr, dev_arr, sizeof(int) * 10);

    // Check that the array on the host has been modified
    for (int i = 0; i < 10; i++) {
        if (arr[i] != (rand() % 100) + 1) {
            err = 1;
            break;
        }
    }

    // Free the device memory
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