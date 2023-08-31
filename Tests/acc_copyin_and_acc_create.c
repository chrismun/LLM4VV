#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a 2D array with random values
    int arr[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            arr[i][j] = rand();
        }
    }

    // Copy the array to the device
    int *dev_arr;
    acc_copyin(dev_arr, arr, N * N * sizeof(int));

    // Create a 2D array with random values on the device
    int *dev_arr2;
    acc_create(dev_arr2, N * N * sizeof(int));

    // Copy the array back to the host
    acc_copyout(arr, dev_arr, N * N * sizeof(int));

    // Verify that the array is the same on the host and device
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (arr[i][j] != dev_arr2[i][j]){
                err = 1;
            }
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