#include <stdlib.h>
#include <stdio.h>
#define SEED 1234
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:declare directive,V:2.7-3.3

// Declare an array to be created in the device memory
#pragma acc declare create(device_array)

// Test function
int test1(){
    int err = 0;
    srand(SEED); // Ensure reproducibility
    
    int host_array[100];
    // Initialize host array
    for(int i = 0; i < 100; ++i){
        host_array[i] = rand() % 100;
    }
    
    // Device array declaration (already marked for creation in device memory above)
    int device_array[100];
    
    // Copy data to device and modify
    #pragma acc parallel loop copyin(host_array)
    for(int i = 0; i < 100; ++i){
        device_array[i] = host_array[i] * 2; // Simple operation to verify functionality
    }
    
    // Copy modified data back to host array for verification
    #pragma acc parallel loop copyout(host_array)
    for(int i = 0; i < 100; ++i){
        host_array[i] = device_array[i];
    }
    
    // Verify the operation
    for(int i = 0; i < 100; ++i){
        if(host_array[i] != (rand() % 100) * 2){
            err++;
        }
    }
    
    return err;
}
#endif

// Main function
int main(){
    int failcode = 0;
    int failed;

    #ifndef T1
    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        if(test1() != 0){
            failed++;
        }
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
    #endif

    return failcode;
}