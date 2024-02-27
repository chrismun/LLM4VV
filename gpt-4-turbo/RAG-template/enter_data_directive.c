#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Example definition for acc_testsuite.h (minimalistic)
// Assuming acc_testsuite.h defines SEED and NUM_TEST_CALLS
// In a real scenario, this should provide a richer testing framework, setup, and utilities.

int test1(){
    int err = 0;
    srand(SEED);
    int n = 1024;
    int* a = (int*)malloc(n * sizeof(int));
    int* b = (int*)malloc(n * sizeof(int));
    
    // Initialize the array with some values
    for (int i = 0; i < n; ++i){
        a[i] = rand() % 100;
    }
    
    // Copy data to the accelerator and allocate space for array b
    #pragma acc enter data copyin(a[0:n]) create(b[0:n])
    
    // Perform some computation on the device
    #pragma acc parallel loop present(a, b)
    for (int i = 0; i < n; ++i){
        b[i] = a[i] + 1;
    }
    
    // Copy modified data back to the host
    #pragma acc exit data copyout(b[0:n])
    
    // Verification step
    for (int i = 0; i < n; ++i){
        if (b[i] != a[i] + 1){
            err++;
        }
    }
    
    free(a);
    free(b);
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}