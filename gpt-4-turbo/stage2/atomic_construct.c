#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define constants for the test
#define SEED 123
#define NUM_TEST_CALLS 1000

// Test: Verify OpenACC atomic update is correct
#ifndef T1
//T1:atomic construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Initial value for the variable to be updated atomically
    int x = 0;

    // Use a large number of iterations to increase the chance of race conditions without atomic operations
    #pragma acc parallel num_gangs(100) vector_length(32)
    {
        // The atomic update should prevent race conditions, resulting in correct final value
        #pragma acc loop reduction(+:x)
        for(int i = 0; i < 10000; ++i) {
            #pragma acc atomic update
            x++;
        }
    }

    // The expected value is the sum of all increments
    if(x != 10000) {
        err = 1; // If not equal, the atomic construct did not work as expected
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0); // Set the failcode bit for test1 failure
    }
#endif
    // Return 0 if success, nonzero if failed
    return failcode;
}