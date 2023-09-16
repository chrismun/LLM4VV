#include "acc_testsuite.h"
#include <stdlib.h>

int async_test() {
    int err = 0;
    int length = 1024;
    
    // Initialize host arrays
    float* a = (float*) malloc(length * sizeof(float));
    float* b = (float*) malloc(length * sizeof(float));
    
    for (int i = 0; i < length; ++i) {
        a[i] = (float)i;
        b[i] = 0.0f;
    }

    // Compute on the device
    #pragma acc parallel loop async
    for (int i = 0; i < length; ++i) {
        b[i] = a[i] * 2.0f + 1.0f;
    }

    // Wait for all computations to finish
    #pragma acc wait

    for (int i = 0; i < length; ++i) {
        if (b[i] != a[i] * 2.0f + 1.0f) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += async_test();
    }
    return failed;
}