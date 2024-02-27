#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SEED 123
#define n 100 // Define the size of the data arrays.
#define m 100 // Define another dimension for the data arrays.
#define PRECISION 0.0001

// Function to test the collapse clause.
int test_collapse() {
    int err = 0;
    srand(SEED);
    float **a = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; ++i) {
        a[i] = (float *)malloc(m * sizeof(float));
    }
    float **b = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; ++i) {
        b[i] = (float *)malloc(m * sizeof(float));
    }

    // Initialize array a with random values, and b with zeros.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = rand() / (float)(RAND_MAX / 10);
            b[i][j] = 0;
        }
    }

#pragma acc data copyin(a[0:n][0:m])
    {
#pragma acc parallel 
        {
#pragma acc loop collapse(2)
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    b[i][j] = a[i][j];
                }
            }
        }
    }

    // Check for errors.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (fabs(b[i][j] - a[i][j]) > PRECISION) {
                err += 1;
            }
        }
        free(a[i]); // Free the allocated space for a
        free(b[i]); // Free the allocated space for b
    }
    free(a); // Free the allocated space for a
    free(b); // Free the allocated space for b
    
    return err;
}

int main() {
    int failcode = 0;

    int failed = test_collapse();
    if (failed != 0) {
        failcode = 1; // Set failcode to 1 if the test fails.
        printf("Collapse clause test failed with %d errors.\n", failed);
    } else {
        printf("Collapse clause test passed.\n");
    }

    return failcode;
}