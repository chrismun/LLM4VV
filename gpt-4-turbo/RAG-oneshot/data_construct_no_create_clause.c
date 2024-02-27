#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef PRECISION
#define PRECISION 1e-5
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

#ifndef n
#define n 1000
#endif

// Function to test the no_create clause
int test_no_create(){
    int err = 0;
    float *a_host = (float *)malloc(n * sizeof(float));
    float *b_host = (float *)malloc(n * sizeof(float));

    // Initialize arrays
    srand(SEED);
    for (int i = 0; i < n; ++i){
        a_host[i] = rand() / (float)(RAND_MAX / 10);
        b_host[i] = -1.0; // Initialize with a different value
    }

    // Allocate 'a' on the device and copy data
    #pragma acc enter data copyin(a_host[0:n])
    
    // 'b' is not allocated on the device explicitly.
    // The no_create clause should ensure 'b' is not created on the device.
    #pragma acc parallel loop no_create(b_host[0:n])
    for(int i = 0; i < n; ++i){
        b_host[i] = a_host[i];
    }

    // Check the result
    for(int i = 0; i < n; ++i){
        if(fabs(b_host[i] + 1.0) > PRECISION){ // b_host should remain unchanged (-1.0) if no_create works correctly
            err += 1;
        }
    }
    
    // Cleanup: Exit data region for 'a'
    #pragma acc exit data delete(a_host[0:n])
    
    free(a_host);
    free(b_host);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_no_create();
    }
    if (failed != 0){
        failcode = 1; // Mark as failed
    }

    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    
    return failcode;
}