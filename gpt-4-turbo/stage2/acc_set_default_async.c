#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Define a simple kernel for testing
#pragma acc routine seq
int simple_kernel(int x) {
    return x + 1;
}

int test_acc_set_default_async(){
    int err = 0;
    const int size = 1024;
    int a[size], a_host[size];
    // Initialize array with known values
    for (int i = 0; i < size; ++i){
        a[i] = i;
        a_host[i] = i; // Keep a host copy for verification
    }

    int default_async_queue = 1; // Choose an async queue number
    
    // Set the default async queue for operations
    acc_set_default_async(default_async_queue);
    
    // Perform a parallel operation asynchronously without specifying the async queue
    #pragma acc parallel loop copy(a[0:size])
    for (int i = 0; i < size; ++i){
        a[i] = simple_kernel(a[i]);
    }

    // Synchronize on the chosen async queue to ensure completion
    acc_wait(default_async_queue);
    
    // Verify the results
    for (int i = 0; i < size; ++i){
        if (a[i] != a_host[i] + 1){
            err++;
            break;
        }
    }

    // Reset the default async queue to initial settings
    acc_set_default_async(0); // Assuming 0 resets to the initial value
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_set_default_async();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    if(failcode == 0){
        printf("Test Passed.\n");
    } else {
        printf("Test Failed.\n");
    }

    return failcode;
}