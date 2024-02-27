#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define VECTOR_SIZE 1024
#define SEED 42
#define NUM_TEST_CALLS 10

// Test function to verify the 'wait' clause implementation.
int test_wait_clause() {
    int err = 0;
    int *a, *b, *c;
    size_t i;

    // Allocate memory for vectors on the host
    a = (int *)malloc(VECTOR_SIZE * sizeof(int));
    b = (int *)malloc(VECTOR_SIZE * sizeof(int));
    c = (int *)malloc(VECTOR_SIZE * sizeof(int));

    // Initialize vectors
    for (i = 0; i < VECTOR_SIZE; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;  // Will store the result of a[i] + b[i]
    }

    // Compute vector addition on the device
    #pragma acc data copyin(a[0:VECTOR_SIZE], b[0:VECTOR_SIZE]) copyout(c[0:VECTOR_SIZE])
    {
        #pragma acc parallel loop
        for (i = 0; i < VECTOR_SIZE; i++) {
            c[i] = a[i] + b[i];
        }

        // The 'wait' clause to ensure the vector addition is complete
        #pragma acc wait
    }

    // Verification step: Check if all results of c[i] are correct (a[i] + b[i])
    for (i = 0; i < VECTOR_SIZE; i++) {
        if (c[i] != a[i] + b[i]) {
            err++;
            break;
        }
    }

    // Clean up resources
    free(a);
    free(b);
    free(c);

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_wait_clause();
    }

    if (failed != 0) {
        failcode = (1 << 0);
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}