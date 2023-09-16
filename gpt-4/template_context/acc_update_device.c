#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>


#define TEST_SIZE 1024

//Test 1: Verify acc_update_device functionality
int test1(){
    int err = 0;
    int *h_data = (int*)malloc(TEST_SIZE * sizeof(int));
    int *d_data;

    // Initialize host data
    for(int i = 0; i < TEST_SIZE; i++){
        h_data[i] = i;
    }

    #pragma acc enter data copyin(h_data[0:TEST_SIZE])
    
    // Update device data with host
    acc_update_device(h_data, TEST_SIZE * sizeof(int));

    d_data = (int *)acc_deviceptr(h_data);

    // Check device data matches host
    #pragma acc parallel loop copyout(d_data[0:TEST_SIZE])
    for(int i = 0; i < TEST_SIZE; i++){
        if(h_data[i] != d_data[i]){
            printf("Mismatch at position %d: host = %d, device = %d\n", i, h_data[i], d_data[i]);
            err = 1;
        }
    }

    #pragma acc exit data delete(h_data)
    free(h_data);
    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Test failed\n");
    }
    else {
        printf("Test passed\n");
    }
    return failcode;
}