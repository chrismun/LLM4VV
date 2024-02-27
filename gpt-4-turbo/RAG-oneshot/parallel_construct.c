#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

// Considering precision for floating-point comparison
#define PRECISION 1e-5

// Utility function to compare arrays and check for errors
int compare_arrays(float *a, float *b, int n) {
    int err = 0;
    for (int i = 0; i < n; ++i) {
        if (fabs(a[i] - b[i]) > PRECISION) {
            err++;
        }
    }
    return err;
}

int main(){
    int n = 1024; // Array size, can be modulated as needed
    float *a = (float *)malloc(n * sizeof(float));
    float *b = (float *)malloc(n * sizeof(float));
    float *sequential_results = (float *)malloc(n * sizeof(float));

    // Initialize arrays
    for(int i = 0; i < n; i++){
        a[i] = i * 1.0f;
        sequential_results[i] = a[i] + 1.0f; // Expected result after sequential addition
    }

    // Parallel region to perform operation
    #pragma acc parallel loop copyin(a[0:n]) copyout(b[0:n])
    for (int i = 0; i < n; ++i) {
        b[i] = a[i] + 1.0f; // Parallel operation
    }

    // Verify results
    int errors = compare_arrays(b, sequential_results, n);

    // Free memory
    free(a);
    free(b);
    free(sequential_results);

    // Verify correctness
    if (errors) {
        printf("Test failed with %d errors.\n", errors);
        return -1;
    } else {
        printf("Test passed.\n");
        return 0;
    }
}