#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        arr[i] = i;
    }

    // Create a copy of the array
    int *arr_copy = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        arr_copy[i] = arr[i];
    }

    // Delete the first element of the array
    #pragma acc parallel delete(arr[0])

    // Check that the first element of the array is deleted
    if (arr[0] != 0) {
        err = 1;
    }

    // Check that the rest of the array is unchanged
    for (int i = 1; i < N; i++) {
        if (arr[i] != arr_copy[i]) {
            err = 1;
        }
    }

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