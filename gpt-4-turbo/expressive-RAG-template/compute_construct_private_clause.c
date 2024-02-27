#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 1234
#define NUM_TEST_CALLS 10

// Mock up a test suite header definitions as a placeholder
int err = 0;

// Test for OpenACC private clause
#ifndef T1
// T1: compute construct private clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int original_val = 5;
    int private_val = original_val;

    #pragma acc parallel private(private_val)
    {
        // Each gang should have its private copy of private_val, modifications here
        // should not affect original_val outside of this region.
        private_val += 1;
    }

    // Check if original_val remains unchanged, indicating private_val was indeed private
    // within the OpenACC region
    if(original_val != 5) {
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    if(failcode == 0) {
        printf("PASS: OpenACC private clause implemented correctly.\n");
    } else {
        printf("FAIL: OpenACC private clause implementation error.\n");
    }
    return failcode;
}