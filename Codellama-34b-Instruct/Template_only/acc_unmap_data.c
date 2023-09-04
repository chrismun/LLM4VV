#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

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

    // Create a device pointer to the array
    int* d_arr;
    acc_map_data(arr, sizeof(int) * 10, &d_arr);

    // Unmap the device pointer
    acc_unmap_data(d_arr);

    // Check that the array is still accessible on the host
    for (int i = 0; i < 10; i++) {
        if (arr[i] != d_arr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device pointer
    acc_free(d_arr);

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