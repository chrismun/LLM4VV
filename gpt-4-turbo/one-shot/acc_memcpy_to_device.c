#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define N 1024
#define SEED 123
#define PRECISION 1e-6

// Function to initialize array with random data
void init_array(double *a, int n) {
    srand(SEED);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (double)(RAND_MAX / 10);
    }
}

// Function to validate the results
int validate(double *a, double *b, int n) {
    int err = 0;
    for (int i = 0; i < n; ++i) {
        if (fabs(b[i] - (a[i] * 2)) > PRECISION) {
            err += 1;
        }
    }
    return err;
}

int main() {
    double *a, *a_device;
    double *b, *b_device;
    int n = N;
    int err = 0;

    a = (double *)malloc(n * sizeof(double));
    b = (double *)malloc(n * sizeof(double));

    // Initialize array with random data
    init_array(a, n);

    // Allocate memory on the device
    a_device = (double *)acc_malloc(n * sizeof(double));
    b_device = (double *)acc_malloc(n * sizeof(double));

    // Copy data to the device
    acc_memcpy_to_device(a_device, a, n * sizeof(double));

    // Perform computation on the device
    #pragma acc parallel loop copyin(a_device[0:n]) copyout(b_device[0:n])
    for (int i = 0; i < n; ++i) {
        b_device[i] = a_device[i] * 2; // Example computation: double each element's value
    }
    
    // Copy result back to host
    acc_memcpy_from_device(b, b_device, n * sizeof(double));
    
    // Validate results
    err = validate(a, b, n);
    if (err) {
        printf("Test FAILED with %d errors.\n", err);
    } else {
        printf("Test PASSED.\n");
    }

    // Cleanup
    acc_free(a_device);
    acc_free(b_device);
    free(a);
    free(b);

    return err;
}