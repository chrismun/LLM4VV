#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define VECTOR_LENGTH 2512

int main() {
    int failcode = 0;
    int failed = 0;

    // Initialize data
    int n = 10000;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Set vector length
    #pragma acc parallel vector_length(VECTOR_LENGTH)
    {
        // Compute vector addition
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                b[i] = a[i] + b[i];
            }
        }
    }

    // Check results
    for (int i = 0; i < n; i++) {
        if (fabs(b[i] - (a[i] + b[i])) > 1e-6) {
            printf("Error at index %d: expected %f, got %f\n", i, a[i] + b[i], b[i]);
            failed++;
        }
    }

    if (failed > 0) {
        printf("Failed %d tests\n", failed);
        failcode = 1;
    } else {
        printf("All tests passed\n");
    }

    return failcode;
}