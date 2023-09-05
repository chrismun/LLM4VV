#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand();
    }

    // Create a device array to store the data
    int* dev_arr = (int*)acc_malloc(sizeof(int) * 10);

    // Copy the data to the device array
    acc_memcpy(dev_arr, arr, sizeof(int) * 10);

    // Create a host array to store the data
    int* host_arr = (int*)malloc(sizeof(int) * 10);

    // Copy the data from the device array to the host array
    acc_memcpy(host_arr, dev_arr, sizeof(int) * 10);

    // Check if the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (host_arr[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free(dev_arr);

    // Free the host array
    free(host_arr);

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