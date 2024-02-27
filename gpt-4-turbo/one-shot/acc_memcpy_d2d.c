#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#ifndef PRECISION
#define PRECISION 0.001
#endif

#ifndef SEED
#define SEED 12345
#endif

#ifndef N
#define N 1024
#endif

int validate_acc_memcpy_d2d(){
    int err = 0;
    srand(SEED);
    float *a_h = (float *)malloc(N * sizeof(float)); // Host array
    float *b_h = (float *)malloc(N * sizeof(float)); // Host array for validation
    float *a_d, *b_d; // Device pointers

    // Initialize host array
    for (int i = 0; i < N; ++i){
        a_h[i] = rand() / (float)(RAND_MAX / 10);
    }

    // Allocate and initialize device memory
    a_d = (float *)acc_malloc(N * sizeof(float));
    b_d = (float *)acc_malloc(N * sizeof(float));
    acc_memcpy_to_device(a_d, a_h, N * sizeof(float)); // Copy data to device

    #pragma acc parallel present(a_d, b_d)
    {
        // Perform device-to-device copy
        acc_memcpy_d2d(b_d, a_d, N * sizeof(float));
    }

    // Copy result back to host for validation
    acc_memcpy_from_device(b_h, b_d, N * sizeof(float));

    // Validate
    for (int i = 0; i < N; ++i){
        if (fabs(b_h[i] - a_h[i]) > PRECISION){
            err++;
        }
    }

    // Cleanup
    acc_free(a_d);
    acc_free(b_d);
    free(a_h);
    free(b_h);

    return err;
}

int main(void){
    int fail = 0;

    fail = validate_acc_memcpy_d2d();

    if (fail) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }

    return fail;
}