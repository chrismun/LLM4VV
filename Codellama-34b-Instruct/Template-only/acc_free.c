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

    // Free the device memory
    acc_free(dev_arr);

    // Check that the device memory has been freed
    if (acc_is_present(dev_arr)) {
        err = 1;
    }

    // Free the host memory
    free(arr);

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