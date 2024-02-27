#include <stdio.h>
#include <stdlib.h>
#include "openacc.h"

#define SEED 1234
#define n 1000
#define PRECISION 0.0001
typedef float real_t;

int test_acc_set_default_async() {
    int errors = 0;
    real_t *host_array = (real_t *)malloc(n * sizeof(real_t));
    real_t *device_array = (real_t *)malloc(n * sizeof(real_t));
    int default_async = 5; // Example async queue number

    // Initialize the host array with random values
    srand(SEED);
    for (int i = 0; i < n; ++i) {
        host_array[i] = rand() / (real_t)(RAND_MAX);
    }

    // Set the default async queue
    acc_set_default_async(default_async);

    // Perform operations on the default async queue
    #pragma acc data copyout(device_array[0:n]) copyin(host_array[0:n])
    {
        // The async clause is omitted, so it uses the default set by acc_set_default_async
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i) {
            device_array[i] = host_array[i] * 2.0;
        }
    }

    // Wait for the specific async queue to complete
    acc_wait(default_async);

    // Check results
    for (int i = 0; i < n; ++i) {
        if (fabs(device_array[i] - (host_array[i] * 2.0)) > PRECISION) {
            errors++;
        }
    }

    // Reset default async queue to the initial value
    acc_set_default_async(acc_async_sync);

    free(host_array);
    free(device_array);
    return errors;
}

int main() {
    int failed = test_acc_set_default_async();
    if (failed) {
        printf("Test FAILED with %d errors.\n", failed);
        return 1;
    } else {
        printf("Test PASSED.\n");
        return 0;
    }
}