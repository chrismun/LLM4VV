#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <openacc.h>

#define SEED 42
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Preparing test data
    int *hostArray = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    for(int i = 0; i < NUM_ELEMENTS; ++i) {
        hostArray[i] = rand();
    }
    
    // Copy data to device
    #pragma acc enter data copyin(hostArray[0:NUM_ELEMENTS])
    
    // Test acc_deviceptr
    void *device_ptr = acc_deviceptr(hostArray);
    if (device_ptr == NULL){
        printf("Data not found on the device as expected.\n");
        err++;
    } else {
        printf("Data found on the device.\n");
    }

    // Test acc_deviceptr with NULL pointer
    void *null_ptr_test = acc_deviceptr(NULL);
    if (null_ptr_test != NULL) {
        printf("Expected NULL but got a non-NULL pointer.\n");
        err++;
    }

    // Cleanup
    #pragma acc exit data delete(hostArray[0:NUM_ELEMENTS])
    free(hostArray);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
        printf("Test failed %d times.\n", failed);
    } else {
        printf("All tests passed successfully.\n");
    }
#endif
    return failcode;
}