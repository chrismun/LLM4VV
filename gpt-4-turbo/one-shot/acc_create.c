#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define n 1000
#define PRECISION 1e-5
#define SEED 12345

typedef float real_t; // Define real_t as needed, float is used here for simplicity

#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test_create() {
    int err = 0;
    srand(SEED);
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t)); // Host memory for verification
    real_t *a_device; // Pointer for device memory

    // Initialize host array for verification purpose
    for (int x = 0; x < n; ++x) {
        a_host[x] = 0;
    }

    #pragma acc data create(a_device[0:n])
    {
        #pragma acc kernels
        {
            // Allocate and initialize memory on the device
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                a_device[x] = rand() / (real_t)(RAND_MAX / 10);
            }
        }

        // Copy initialized device memory to host for verification
        #pragma acc update host(a_device[0:n])
    }

    // Verification
    for (int x = 0; x < n; ++x) {
        if (fabs(a_device[x] - a_host[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a_host);
    return err;
}
#endif // T1

int main() {
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < 1; ++x) { // Assuming a single call suffices for this demonstration
        failed += test_create();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif // T1

    if (failcode) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }

    return failcode;
}