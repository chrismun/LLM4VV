#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Function prototype with nohost clause - to be run on accelerator only
#pragma acc routine seq nohost
void increment_value(int *a);

// Function definition
#pragma acc routine seq nohost
void increment_value(int *a) {
    *a = *a + 1;
}

int test1(){
    int err = 0;
    int a = 5;
    int original_a = a;
    
    // Using OpenACC parallel region to invoke the increment_value function
    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        #pragma acc loop seq
        for (int i = 0; i < 1; ++i){   
            increment_value(&a);
        }
    }

    // Check if the value has been incremented
    if (a != original_a + 1) {
        err += 1; // Increment error if the value is not as expected
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    return failcode;
}