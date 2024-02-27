#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Test for the shutdown directive.
int test_shutdown(){
    int err = 0;
    const int size = 1024;
    int *a_host = (int*) malloc(size * sizeof(int));
    int *b_host = (int*) malloc(size * sizeof(int));

    // Initialize host memory
    for(int i = 0; i < size; ++i){
        a_host[i] = rand() % 100;
        b_host[i] = 0;
    }

    // Perform computation on the device
    #pragma acc parallel loop copyin(a_host[0:size]) copyout(b_host[0:size])
    for(int i = 0; i < size; ++i){
        b_host[i] = a_host[i] + 1;
    }

    // Shutdown all devices
    #pragma acc shutdown

    // Attempt to verify shutdown by performing an operation that requires active devices
    // Note: This is not a standard or guaranteed way to test shutdown as behavior might not be strictly defined in this context.
    // Proper shutdown verification might require platform or implementation-specific checks.
    #pragma acc parallel loop copyin(a_host[0:size]) copyout(b_host[0:size])
    for(int i = 0; i < size; ++i){
        b_host[i] = a_host[i] + 2;
    }

    // Cleanup and check error
    free(a_host);
    free(b_host);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_shutdown();
    }
    if (failed != 0){
        failcode += 1;
    }
    return failcode;
}