#include <stdio.h>
#include <stdlib.h>

// Define some constants for the test
#define SEED 12345
#define NUM_TEST_CALLS 10
#define N 100 // Size of accumulation

#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int total = 0;

    // OpenACC region with seq clause
    #pragma acc parallel
    {
        #pragma acc loop seq
        for(int i = 1; i <= N; i++){
            total += i;
        }
    }

    // The expected result if executed sequentially
    int expected = (N * (N + 1)) / 2;

    // Check if the result matches the expected value
    if(total != expected){
        err = 1; // Set error if the computation is incorrect
    }

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
    
    if(failcode == 0){
        printf("Test Passed.\n");
    } else {
        printf("Test Failed.\n");
    }
    return failcode;
}