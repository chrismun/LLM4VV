#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 100 // Size of the arrays
#define PRECISION 0.00001

int test_acc_update_device_self() {
    int i, err = 0;
    float *a_host = (float *)malloc(n * sizeof(float));
    float *a_device_copy = (float *)malloc(n * sizeof(float));

    // Initialize array on host
    srand(SEED);
    for (i = 0; i < n; i++) {
        a_host[i] = rand() / (float)RAND_MAX;
        a_device_copy[i] = a_host[i]; // Copy for later validation
    }

    // Update device with host array's initial values
    #pragma acc enter data copyin(a_host[0:n])

    // Modify array on the host
    for (i = 0; i < n; i++) {
        a_host[i] *= 2;
    }

    // Reflect host modifications to the device
    #pragma acc update device(a_host[0:n])

    // Modify array on device
    #pragma acc parallel loop present(a_host)
    for (i = 0; i < n; i++) {
        a_host[i] += 1;
    }

    // Reflect device modifications back to the host
    #pragma acc update self(a_host[0:n])

    // Verify the results
    for (i = 0; i < n; i++) {
        if (fabs(a_host[i] - (a_device_copy[i] * 2 + 1)) > PRECISION) {
            err++;
        }
    }

    #pragma acc exit data delete(a_host[0:n])

    free(a_host);
    free(a_device_copy);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = test_acc_update_device_self();

    if (failed != 0) {
        failcode = 1;
        printf("Test failed with %d errors.\n", failed);
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}