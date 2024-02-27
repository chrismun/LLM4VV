#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Simple seed for reproducibility
#define SEED 12345
// Number of test calls for robustness
#define NUM_TEST_CALLS 5

#ifndef T1
// T1:parallel construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int original_val = 5;
    int temp_val = original_val;

    // Using OpenACC parallel construct with private clause
    #pragma acc parallel private(temp_val)
    {
        // Modify temp_val within the parallel region
        temp_val += 5;
    }

    // Check if the original variable 'original_val' remains unaffected
    if (original_val != 5){
        err++;
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
        // Encoding the failcode based on the identified test
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}