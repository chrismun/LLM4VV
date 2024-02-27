#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// This macro is used to seed the random number generator for reproducibility.
#define SEED 12345

// Number of test calls to handle statistical variations in execution.
#define NUM_TEST_CALLS 5

#ifndef T1
// T1:parallel construct num_gangs clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    // Expected number of gangs, adjust as necessary.
    int expected_gangs = 8;
    
    // Testing variable, will be updated in parallel region
    int actual_gangs = 0;
    
    // Populate a large array to ensure parallel execution
    size_t arr_size = 100000;
    float *data = (float *)malloc(arr_size * sizeof(float));
    for (size_t i = 0; i < arr_size; ++i) {
        data[i] = i;
    }
    
    // OpenACC parallel region to test num_gangs clause
    #pragma acc parallel num_gangs(expected_gangs) copyout(actual_gangs)
    {
        // Atomic capture ensures safe update in parallel environment
        #pragma acc atomic capture
        actual_gangs++;
    }
    
    // Verify if the actual number of gangs matches the expected number.
    if (actual_gangs != expected_gangs) {
        printf("Error: Expected %d gangs, but got %d.\n", expected_gangs, actual_gangs);
        err = 1;
    }
    
    free(data);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}