#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 1e-5

int test_wait_clause() {
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    float *c = (float *)malloc(n * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (float)(RAND_MAX);
        b[i] = rand() / (float)(RAND_MAX);
        c[i] = 0.0f;  // Expected to hold result of a[i] + b[i]
    }

    // Perform computation on device
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        // First operation without a wait clause, just a precursor to the real test
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i) {
            c[i] = a[i] + b[i];
        }

        // Here's where we test the wait clause
        // Let's assume we're waiting for all previously enqueued operations to complete
        #pragma acc parallel loop wait
        for (int i = 0; i < n; ++i) {
            c[i] = c[i] * 2; // Assuming previous operation on `c` is done, double the elements
        }
    }

    // Verify correctness of the operation
    for (int i = 0; i < n; ++i) {
        if (fabs(c[i] - (a[i] + b[i]) * 2) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main() {
    int failcode = 0;
    int failures = test_wait_clause();

    if (failures) {
        failcode = 1; // Set failcode non-zero if there were errors.
        printf("Test FAILED with %d errors.\n", failures);
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}