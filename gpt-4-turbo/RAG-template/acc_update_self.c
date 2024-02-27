#include <stdio.h>
#include <stdlib.h>
#include "openacc.h"

#define SEED 123
#define NUM_ELEMENTS 1000
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    int *host_array = (int *)malloc(sizeof(int) * NUM_ELEMENTS);
    // Initialize array
    for(int i = 0; i < NUM_ELEMENTS; ++i){
        host_array[i] = i;
    }

    // Data allocation on the device
    #pragma acc enter data copyin(host_array[0:NUM_ELEMENTS])

    // Modify the data on the device
    #pragma acc parallel loop present(host_array)
    for(int i = 0; i < NUM_ELEMENTS; ++i){
        host_array[i] += 1; // Increment every element by 1
    }

    // Update the data back to host memory
    acc_update_self(host_array, sizeof(int) * NUM_ELEMENTS);

    // Validate the modification
    for(int i = 0; i < NUM_ELEMENTS; ++i){
        if(host_array[i] != i + 1){
            err += 1;
        }
    }

    // Cleanup
    #pragma acc exit data delete(host_array[0:NUM_ELEMENTS])
    free(host_array);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    if (failcode == 0) {
        printf("TEST PASSED\n");
    } else {
        printf("TEST FAILED\n");
    }
    return failcode;
}