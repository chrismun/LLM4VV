#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test for num_workers clause
int test_num_workers(){
    int err = 0;
    const int num_elements = 1024; // Total number of elements to be processed
    const int num_workers = 4; // Desired number of workers
    int *data = (int *)malloc(sizeof(int) * num_elements);
    int expected_sum = 0;
    int computed_sum = 0;
    
    // Initialize data and compute expected result
    for (int i = 0; i < num_elements; ++i) {
        data[i] = 1; // Each element contributes 1 to the sum
        expected_sum += data[i]; // Accumulate the expected sum
    }
    
    // Compute sum using OpenACC with a specified number of workers
    #pragma acc parallel loop num_workers(num_workers) reduction(+:computed_sum)
    for (int i = 0; i < num_elements; ++i) {
        computed_sum += data[i];
    }
    
    // Verify if the computed sum matches the expected sum
    if (computed_sum != expected_sum) {
        err = 1; // Indicates an error if there's a mismatch
    }
    
    free(data);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_num_workers();
    }
    if (failed != 0){
        failcode += 1; // Set the first bit if there's a failure
    }

    return failcode;
}