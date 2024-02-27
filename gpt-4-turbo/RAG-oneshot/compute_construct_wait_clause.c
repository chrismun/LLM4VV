#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Include an appropriate header or define the following accordingly based on your setup.
#define n 1000
#define SEED 123
#define PRECISION 0.0001

// Function to test the wait clause
int test_wait_clause() {
    int err = 0;
    srand(SEED);
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));

    // Initialize arrays with random values
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (float)(RAND_MAX / 10);
        b[i] = 0;
    }

    // Perform operations on the device
    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i) {
                b[i] = a[i] * 2.0f;
            }
        }
        // Use the wait clause to ensure completion
        #pragma acc wait
    }

    // Verify the results are as expected
    for (int i = 0; i < n; ++i) {
        if (fabs(b[i] - (a[i] * 2.0f)) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed = test_wait_clause();

    if (failed != 0) {
        failcode = 1;
        printf("Test FAILED with %d errors.\n", failed);
    } else {
        printf("Test PASSED.\n");
    }

    return failcode;
}