#include <stdio.h>
#include <stdlib.h>
#include "openacc.h"

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

int test_default_async_functionality(){
    int err = 0;
    const int size = 1024;
    int *host_array = (int*) malloc(size * sizeof(int));
    int *device_array;
    
    // Initialize host array with random data
    srand(SEED);
    for(int i = 0; i < size; i++) {
        host_array[i] = rand() % 100; // Random values between 0 to 99
    }
    
    // Allocate memory on the device
    device_array = (int*) acc_malloc(size * sizeof(int));
    if (device_array == NULL) {
        printf("Error allocating memory on the device.\n");
        free(host_array);
        return 1; // signifies an error
    }
    
    // Set default async queue to 1 and copy data to device
    acc_set_default_async(1);
    #pragma acc enter data copyin(host_array[0:size]) async

    // Wait for async operation to complete
    acc_wait(1);
    
    // Perform a simple operation on the data in the default async queue
    #pragma acc parallel loop async
    for (int i = 0; i < size; i++) {
        device_array[i] = host_array[i] + 1;
    }
    
    // Copy modified data back to host in the default async queue
    #pragma acc exit data copyout(host_array[0:size]) async
    
    // Wait for all pending async operations to complete
    acc_wait(1);

    // Verification
    for(int i = 0; i < size; i++) {
        if (host_array[i] != (rand() % 100) + 1) { // considering initial random value + 1
            err++;
            break;
        }
    }

    // Cleanup
    acc_free(device_array);
    free(host_array);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_default_async_functionality();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    
    return failcode;
}