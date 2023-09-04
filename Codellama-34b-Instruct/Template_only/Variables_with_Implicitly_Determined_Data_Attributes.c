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

    // Create a device array of integers
    int* dev_arr = (int*)acc_malloc(sizeof(int) * 10);

    // Copy the host array to the device array
    acc_memcpy(dev_arr, arr, sizeof(int) * 10);

    // Create a device array of integers with implicitly determined data attributes
    int* dev_arr_implicit = (int*)acc_malloc(sizeof(int) * 10);

    // Copy the host array to the device array with implicitly determined data attributes
    acc_memcpy(dev_arr_implicit, arr, sizeof(int) * 10);

    // Check that the device array with implicitly determined data attributes has the same values as the host array
    for (int i = 0; i < 10; i++) {
        if (dev_arr_implicit[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device arrays
    acc_free(dev_arr);
    acc_free(dev_arr_implicit);

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