#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024
#define SEED 42
#define PRECISION 0.001

// Function to verify the async behavior
int verify_async() {
    int errors = 0;
    float *input = (float*) malloc(N * sizeof(float));
    float *output = (float*) malloc(N * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        input[i] = i;
        output[i] = 0;
    }

    // Perform data copy and computation asynchronously
    #pragma acc data copyin(input[0:N]) copyout(output[0:N])
    {
        #pragma acc parallel loop async(1)
        for (int i = 0; i < N; i++) {
            output[i] = input[i] + 1;
        }

        // Use wait to ensure all operations in the async queue are completed before verification
        #pragma acc wait(1)
    }

    // Verify outputs
    for (int i = 0; i < N; i++) {
        if (abs(output[i] - (input[i] + 1)) > PRECISION) {
            errors++;
        }
    }

    free(input);
    free(output);

    return errors;
}

int main() {
    int failcode = 0;

    // Test the async clause verification
    int failed = verify_async();

    if (failed != 0) {
        printf("Test failed with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}