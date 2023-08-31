#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a 2D array with random values
    int arr[N][M];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            arr[i][j] = rand() % 100;
        }
    }

    // Map the array to the device
    acc_map_data(arr, N, M, ACC_MAP_WRITE);

    // Modify the array on the device
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            arr[i][j] = arr[i][j] * 2;
        }
    }

    // Unmap the array from the device
    acc_unmap_data(arr, N, M, ACC_MAP_WRITE);

    // Check if the array has been modified correctly
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (arr[i][j] != arr[i][j] * 2){
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