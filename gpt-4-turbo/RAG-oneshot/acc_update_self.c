#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "openacc.h"

#define N 1024
#define SEED 42
#define PRECISION 0.00001

// Mockup function for evaluating test success
void evaluate(int errors) {
    if (errors == 0) {
        printf("Test PASSED\n");
    } else {
        printf("Test FAILED with %d errors\n", errors);
    }
}

int main() {
    int errors = 0;
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));
  
    // Initialize array 'a' on the host
    for (int i = 0; i < N; ++i) {
        a[i] = i * 1.0f;
        b[i] = 0.0f;
    }

    // Copy data to the device
    #pragma acc data copy(a[0:N]) copyout(b[0:N])
    {
        // Modify array 'a' on the device
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i) {
            a[i] = a[i] + 1.0f;
        }
  
        // Copy modified array 'a' back to 'b' on the host using acc_update_self
        #pragma acc update self(a[0:N])
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i) {
            b[i] = a[i];
        }
    }

    // Verify that host array 'b' is updated correctly
    for (int i = 0; i < N; ++i) {
        if (fabs(b[i] - (i + 1.0f)) > PRECISION) {
            errors++;
        }
    }

    evaluate(errors);

    free(a);
    free(b);

    return errors == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}