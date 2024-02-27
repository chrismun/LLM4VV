#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 0.0001

int test_device_type_gpu() {
    int err = 0;
    float *a = (float *)malloc(n * sizeof(float));
    float *b_gpu = (float *)malloc(n * sizeof(float));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (float)RAND_MAX;
        b_gpu[x] = 0.0f;
    }

    // Attempt to offload to GPU
    #pragma acc data copyin(a[0:n]) copyout(b_gpu[0:n]) device_type(acc_device_nvidia)
    {
        #pragma acc parallel loop device_type(acc_device_nvidia)
        for (int x = 0; x < n; ++x) {
            b_gpu[x] = a[x] + 1;
        }
    }

    // Check results
    for (int x = 0; x < n; ++x) {
        if (fabs(b_gpu[x] - (a[x] + 1)) > PRECISION) {
            err++;
        }
    }

    free(a);
    free(b_gpu);

    return err;
}

int main() {
    srand(SEED);
    int failcode = 0;

    int failed_gpu = test_device_type_gpu();
    if (failed_gpu != 0) {
        printf("GPU test failed with %d errors.\n", failed_gpu);
        failcode |= 1; // Mark as a failure.
    } else {
        printf("GPU test passed.\n");
    }

    return failcode;
}