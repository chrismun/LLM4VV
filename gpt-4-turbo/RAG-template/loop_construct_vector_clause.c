#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define ARRAY_SIZE 1024
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    int a[ARRAY_SIZE];

    // Initialize the array
    for(int i = 0; i < ARRAY_SIZE; ++i){
        a[i] = rand() % 100; // Assign a random value between 0 and 99
    }

    // Parallel region to execute the loop iterations in SIMD/vector mode
    #pragma acc parallel vector_length(128)
    {
        #pragma acc loop vector
        for(int i = 0; i < ARRAY_SIZE; ++i){
            a[i] += 1; // Increment each element by 1
        }
    }

    // Validate the results
    for(int i = 0; i < ARRAY_SIZE; ++i){
        if(a[i] % 100 == 0) { // Considering initial values were in range 0-99, valid incremented values are in range 1-100
            // If the incremented value is exactly 100, it means the original value was 99, which is valid
            continue;
        }
        else if(a[i] % 100 == 1) { // If the incremented value modulo 100 is 1, it indicates correct increment
            continue;
        }
        else{
            err++; // Any other value indicates an error
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1(); // Accumulate errors from individual test runs
    }
    if (failed != 0){
        failcode = failcode + (1 << 0); // Encode test failure in failcode
        printf("Test FAILED with %d errors.\n", failed);
    }
    else {
        printf("Test PASSED.\n");
    }
    return failcode;
}