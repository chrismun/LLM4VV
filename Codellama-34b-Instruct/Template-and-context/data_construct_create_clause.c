#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array on the device
    int *arr = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the array with random values
    for (int i = 0; i < 10; i++) {
        arr[i] = rand();
    }

    // Create a new array on the host
    int *arr_host = (int *)malloc(sizeof(int) * 10);

    // Copy the array from the device to the host
    acc_memcpy(arr_host, arr, sizeof(int) * 10);

    // Check that the arrays are equal
    for (int i = 0; i < 10; i++) {
        if (arr_host[i] != arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the arrays
    acc_free(arr);
    free(arr_host);

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