#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#define SEED 1234
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

void vector_add(float *x, float *y, float *z, int n) {
#pragma acc kernels async(1)
    for (int i = 0; i < n; i++) {
        z[i] = x[i] + y[i];
    }
}

int test_wait_operations(){
    float *x, *y, *z;
    int err = 0;
    // Allocation on host
    x = (float*) malloc(NUM_ELEMENTS * sizeof(float));
    y = (float*) malloc(NUM_ELEMENTS * sizeof(float));
    z = (float*) malloc(NUM_ELEMENTS * sizeof(float));

    // Initialize data
    for(int i = 0; i < NUM_ELEMENTS; i++){
        x[i] = rand() / (float)RAND_MAX;
        y[i] = rand() / (float)RAND_MAX;
        z[i] = 0.0f;
    }

    // Offload the computation to device
    vector_add(x, y, z, NUM_ELEMENTS);
    
    // Wait for asynchronous operations to complete using acc_wait and verify execution
#pragma acc wait(1)
    for(int i = 0; i < NUM_ELEMENTS; i++){
        if(z[i] != x[i] + y[i]){
            err++;
            break;
        }
    }

#pragma acc wait_all
    // Additional data-independent synchronization to test acc_wait_all

    // Clean up
    free(x);
    free(y);
    free(z);

    return err;
}

int main() {
    srand(SEED);
    int failed = 0;

    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_wait_operations();
    }

    if (failed != 0){
        printf("Test FAILED: Errors encountered during acc_wait operations tests.\n");
        return 1;
    }
    
    printf("Test PASSED: All acc_wait operations verified successfully.\n");
    return 0;
}