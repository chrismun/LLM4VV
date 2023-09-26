#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;

    // Declare a function that will be compiled for an accelerator
    void accelerator_function();

    // Declare a function that will be compiled for the host
    void host_function();

    // Define the accelerator function
    #pragma acc routine(accelerator_function)
    void accelerator_function(){
        // Do some accelerator-specific work
        printf("Hello from the accelerator!\n");
    }

    // Define the host function
    #pragma acc routine(host_function)
    void host_function(){
        // Do some host-specific work
        printf("Hello from the host!\n");
    }

    // Call the accelerator function
    accelerator_function();

    // Call the host function
    host_function();

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
    }

    return failcode;
}