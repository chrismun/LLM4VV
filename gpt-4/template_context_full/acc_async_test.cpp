#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

int test_async_operation() {
    int err = 0;
    srand(SEED);

    // Allocate space for a large array
    int n = 1<<20;
    float *data = (float*)malloc(n * sizeof(float));

    // Initialize the array with random numbers
    for (int i = 0; i < n; i++) {
        data[i] = rand() / (float)RAND_MAX;
    }

    // Create an async operation: copy the array to the device
    #pragma acc enter data copyin(data[0:n]) async(0)

    // Test if the async operation has finished
    if (acc_async_test(0) != 0) {
        err = 1;
    }

    // Make sure it has finished before moving on
    #pragma acc wait(0)

    // Free the data on the device
    #pragma acc exit data delete(data[0:n])

    // free the allocated memory
    free(data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_async_operation();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}