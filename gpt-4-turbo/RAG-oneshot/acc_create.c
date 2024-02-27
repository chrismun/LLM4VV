#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>  // Ensure you're linking against an OpenACC-capable compiler/runtime
#include <math.h>

#define SEED 12345
#define PRECISION 0.001

#ifndef NUM_ELEMENTS
#define NUM_ELEMENTS 1024
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Test function to validate 'acc_create'
int test_acc_create(){
    int err = 0;
    float * a = (float *)malloc(NUM_ELEMENTS * sizeof(float));
    float * device_a;
    
    // Initialize array 'a' with random values
    srand(SEED);
    for (int i = 0; i < NUM_ELEMENTS; ++i){
        a[i] = rand() / (float)(RAND_MAX / 10);
    }

    // Allocate device memory corresponding to 'a' but do not copy data
    #pragma acc data create(a[0:NUM_ELEMENTS])
    {
        device_a = acc_create(a, NUM_ELEMENTS * sizeof(float));
        // Verify if acc_create returned a device pointer
        if(device_a == NULL){
            printf("acc_create failed to allocate device memory.\n");
            err++;
        }
    }

    // Clean up and return error count
    free(a);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed += test_acc_create();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
        printf("Some tests failed.\n");
    } else {
        printf("All tests passed successfully!\n");
    }

    return failcode;
}