#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#ifndef PRECISION
#define PRECISION 1e-6
#endif

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_ELEMENTS
#define NUM_ELEMENTS 1024
#endif

// Test function to validate implicit behavior of scalar and aggregate variables
int test_implicit_data_attributes() {
    int err = 0;
    int scalar_variable = 10;
    float *array_variable = (float*) malloc(NUM_ELEMENTS * sizeof(float));

    // Initialize array_variable with random values
    srand(SEED);
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        array_variable[i] = rand() / (float)(RAND_MAX / 10);
    }

    // Expect scalar_variable to be treated as firstprivate and array_variable as copy for kernels construct
    #pragma acc kernels default(none) // Explicitly specifying default(none) for demonstration
    {
        scalar_variable += 1; // This will cause an error if not treated as firstprivate
        
        #pragma acc loop
        for (int i = 0; i < NUM_ELEMENTS; ++i) {
            array_variable[i] += scalar_variable; // Implicitly expects array_variable to be treated as copy
        }
    }

    // Verification
    srand(SEED);
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        float expected_value = rand() / (float)(RAND_MAX / 10) + scalar_variable;
        if (fabs(array_variable[i] - expected_value) > PRECISION) {
            err++;
        }
    }

    free(array_variable);
    return err;
}

int main() {
    int failcode = 0;
    int failed = test_implicit_data_attributes();
    
    if (failed != 0) {
        printf("Test failed with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}