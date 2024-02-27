#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Defining constants for the test 
#define SEED 123456
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 1000

int test1(){
    int err = 0;
    int a[ARRAY_SIZE];
    int expected_value = 5;
    
    // Initialize array with OpenACC parallel construct
    #pragma acc parallel loop
    for(int i = 0; i < ARRAY_SIZE; i++) {
        a[i] = expected_value;
    }

    // Check if the array is initialized as expected
    for(int i = 0; i < ARRAY_SIZE; i++) {
        if(a[i] != expected_value) {
            err = 1; // Error if any array value does not match the expected value
            break;
        }
    }

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
    
    if(failcode == 0) {
        printf("PASS: OpenACC parallel construct test passed.\n");
    } else {
        printf("FAIL: OpenACC parallel construct test failed.\n");
    }

    return failcode;
}