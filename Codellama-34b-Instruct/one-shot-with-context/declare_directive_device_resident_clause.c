#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int main() {
    int failcode = 0;
    int failed;

    // Allocate memory in the current device memory
    real_t *a = (real_t *)acc_malloc(n * sizeof(real_t));
    real_t *b = (real_t *)acc_malloc(n * sizeof(real_t));

    // Initialize the memory with random values
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Copy the memory to the accelerator
    #pragma acc data copyin(a[0:n])
    {
        // Copy the memory back to the host
        #pragma acc kernels copyout(b[0:n])
        {
            // Verify that the memory is accessible from the accelerator
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }

    // Verify that the memory is accessible from the host
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            failcode = failcode + (1 << 0);
        }
    }

    // Free the memory
    acc_free(a);
    acc_free(b);

    return failcode;
}