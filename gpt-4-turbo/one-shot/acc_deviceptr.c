#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <openacc.h>

#define n 1024
#define SEED 123
#define PRECISION 1e-6

int test_deviceptr() {
    int err = 0;
    float *a, *b, *d_a;
    
    // Allocate host memory
    a = (float *)malloc(n * sizeof(float));
    b = (float *)malloc(n * sizeof(float));
    
    // Initialize host memory
    srand(SEED);
    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (float)(RAND_MAX / 10);
    }
    
    // Allocate device memory and copy data to device
    d_a = (float *)acc_malloc(n * sizeof(float));
    acc_memcpy_to_device(d_a, a, n * sizeof(float));
    
    // Perform calculation on device using acc deviceptr
    #pragma acc parallel loop deviceptr(d_a)
    for (int i = 0; i < n; ++i) {
        d_a[i] = sqrtf(d_a[i]);
    }
    
    // Copy result back to host
    acc_memcpy_from_device(b, d_a, n * sizeof(float));
    
    // Verify results
    for (int i = 0; i < n; ++i) {
        if (fabs(sqrtf(a[i]) - b[i]) > PRECISION) {
            err++;
        }
    }
    
    // Free device and host memory
    acc_free(d_a);
    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int errors = test_deviceptr();
    
    if (errors != 0) {
        printf("Test failed with %d errors.\n", errors);
        failcode = 1;
    } else {
        printf("Test passed.\n");
    }
    
    return failcode;
}