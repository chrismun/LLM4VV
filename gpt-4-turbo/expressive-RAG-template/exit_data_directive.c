#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 1
#endif

// Test for exit data directive
// T1: exit data directive, V: 2.7-3.3
int test1(){
    int err = 0;
    const int size = 1024;
    int *host_array = (int*) malloc(size * sizeof(int));
    int original_value = 0;

    // Initialize array and set a distinct value to verify later
    srand(SEED);
    for(int i = 0; i < size; ++i){
        host_array[i] = rand();
        original_value ^= host_array[i]; // XOR to create a simple aggregate check
    }

    // Enter data to device
    #pragma acc enter data copyin(host_array[0:size])

    // Example computation on device to justify data presence (Not modifying host_array here)
    #pragma acc parallel loop present(host_array[0:size])
    for(int i = 0; i < size; ++i){
        host_array[i] += 1;
    }

    // Exit data from device
    #pragma acc exit data delete(host_array[0:size])

    // Verify host_array was not modified by device operation due to deletion
    int verify_value = 0;
    for(int i = 0; i < size; ++i){
        verify_value ^= host_array[i];
    }

    if(verify_value != original_value){
        // If values don't match, error has occurred
        err = 1;
    }

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
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}