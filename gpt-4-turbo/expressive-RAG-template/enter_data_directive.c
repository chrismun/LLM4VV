#include <stdlib.h> // For rand(), srand()
#include <openacc.h> // OpenACC API
#include "acc_testsuite.h"

#ifndef T1
// T1: enter data directive, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int size = 1024;
    float *hostArray = (float*)malloc(size * sizeof(float));
    float *deviceArrayCheck = (float*)malloc(size * sizeof(float));
    
    // Initialize hostArray with random values
    for (int i = 0; i < size; ++i) {
        hostArray[i] = (float)rand() / RAND_MAX;
    }

    // Copy data from host to device
    #pragma acc enter data copyin(hostArray[0:size])

    // Check if data is present on the device
    #pragma acc parallel loop present(hostArray)
    for (int i = 0; i < size; ++i) {
        // Just a dummy operation to force using the variable
        hostArray[i] = hostArray[i];
    }
    
    // Copy data back to host to check
    #pragma acc update host(hostArray[0:size])

    // Validate all values to ensure they were transferred correctly and weren't altered
    for (int i = 0; i < size; ++i) {
        if (hostArray[i] != deviceArrayCheck[i]) {
            err++;
        }
    }

    // Cleanup
    #pragma acc exit data delete(hostArray[0:size])
    free(hostArray);
    free(deviceArrayCheck);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test1() != 0) {
            failed++;
        }
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}