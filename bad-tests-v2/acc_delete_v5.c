#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array on the device
    int *arr = (int *)acc_malloc(SIZE * sizeof(int));

    // Initialize the array on the device
    #pragma acc parallel loop present(arr)
    for(int i = 0; i < SIZE; i++){
        arr[i] = i;
    }

    // Delete the array on the device
    #pragma acc delete(arr)

    // Check if the array is still in device memory
    #pragma acc parallel loop present(arr)
    for(int i = 0; i < SIZE; i++){
        if(arr[i] != i){
            err = 1;
            break;
        }
    }

    // Free the array on the device
    acc_free(arr);

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