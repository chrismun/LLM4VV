#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Generate a random array of integers
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++){
        arr[i] = rand();
    }

    // Create a new array with the same size as arr
    int *new_arr = (int *)malloc(sizeof(int) * N);

    // Copy the contents of arr to new_arr using the copyin directive
    #pragma acc parallel loop copyin(arr[0:N])
    for (int i = 0; i < N; i++){
        new_arr[i] = arr[i];
    }

    // Check if the contents of new_arr are the same as arr
    for (int i = 0; i < N; i++){
        if (new_arr[i] != arr[i]){
            err = 1;
            break;
        }
    }

    // Free the memory allocated for arr and new_arr
    free(arr);
    free(new_arr);

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