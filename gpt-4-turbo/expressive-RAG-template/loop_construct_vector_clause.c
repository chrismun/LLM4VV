#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Make sure to include the OpenACC header

#define SEED 12345
#define NUM_TEST_CALLS 10
#define ARRAY_SIZE 1000

// Utility function to check for errors
static int check_results(float *data, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        if (data[i] != i * 2.0f) {
            printf("Error at element %d: Expected %f, got %f\n", i, i*2.0f, data[i]);
            return 1;
        }
    }
    return 0;
}

#ifndef T1
// T1: loop construct vector clause, V:2.7-3.3
int test1(){
    int err = 0;
    float data[ARRAY_SIZE];
    srand(SEED);

    // Initialize data array
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data[i] = i;
    }

    // Applying the OpenACC parallel construct with the vector clause
    #pragma acc parallel loop vector_length(128)
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data[i] *= 2.0f; // Simple operation to ensure vectorization can be applied
    }

    // Check for correctness
    err = check_results(data, ARRAY_SIZE);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0; // Initialize to 0 to make sure we account for all cases.
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        // If there's any failure, adjust the failcode accordingly
        failcode += (1 << 0);
    }
#endif
    // Return failcode as an indicator of the test result.
    return failcode;
}