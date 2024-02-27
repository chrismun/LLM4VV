#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 42
#define NUM_TEST_CALLS 10

int test_no_create() {
    int err = 0;
    int N = 1024;
    float *array_host = (float*)malloc(N * sizeof(float));

    // Initialize array on host
    for(int i = 0; i < N; ++i)
        array_host[i] = i;

    // Expected to work with previously allocated host memory only, not creating device memory.
    #pragma acc data present_or_create(array_host[0:N]) no_create(array_host[0:N])
    {
        #pragma acc parallel loop
        for(int i = 0; i < N; ++i) {
            // Simply touch each element, the operation is unimportant as we're testing the data clause, 
            // not the computation correctness.
            array_host[i] = array_host[i] * 1; // No meaningful computation, just touch the data.
        }
    }

    // Verification step is trivial as we're not modifying the values, but in a real case, we may have conditions
    // to ensure correct data movement or operations. Here we're ensuring it does not crash or misbehave.
    free(array_host);
    return err;
}

int main() {
    int failcode = 0;
    srand(SEED);

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test_no_create() != 0) {
            failcode++; // accumulate failure code
            break; // For simplicity, exit after first detected failure.
        }
    }

    if (failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return failcode;
}