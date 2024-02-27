#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Seed for randomness
#define SEED 12345
// Number of times to call the test function for more reliable testing
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    // Use a fixed size for simplicity
    int n = 1024;
    // Allocate memory for an array to test on
    int *test_array = (int *)malloc(sizeof(int) * n);

    // Initialize array elements
    for(int i = 0; i < n; ++i){
        test_array[i] = i;
    }

    // Using OpenACC to parallelize loop among workers in a single gang.
    // Attempt to modify array elements in parallel. 
    // The correctness check will validate parallel execution.
    #pragma acc parallel num_gangs(1) 
    {
        #pragma acc loop worker // should distribute iterations among workers
        for(int i = 0; i < n; ++i){
            // Arbitrary operation to ensure work is done
            test_array[i] += 1;
        }
    }

    // Check results
    for(int i = 0; i < n; ++i){
        if(test_array[i] != i + 1){
            // If any element does not match its expected value, record error
            err++;
        }
    }
    
    // free allocated memory
    free(test_array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    // Print message based on the result
    if (failcode == 0) {
        printf("PASS: OpenACC worker clause tests passed.\n");
    } else {
        printf("FAIL: OpenACC worker clause tests failed.\n");
    }
    return failcode;
}