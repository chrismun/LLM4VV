#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Allocate memory for the source and destination arrays
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize the source array with random values
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    // Copy the source array to the device
    #pragma acc enter data copyin(a[0:n])

    // Copy the source array to the destination array on the device
    #pragma acc kernels copyout(b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            b[x] = a[x];
        }
    }

    // Copy the destination array from the device to the host
    #pragma acc exit data copyout(b[0:n])

    // Verify that the destination array contains the correct values
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            failcode = failcode + (1 << 0);
        }
    }

    // Free the memory allocated for the source and destination arrays
    free(a);
    free(b);

    return failcode;
}