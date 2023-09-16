#include <stdio.h>
#include "openacc.h"
#include <stdlib.h>

//T1:compute construct async clause, V:2.7-3.3
int test1() {
    // Initialize error to zero
    int err = 0;

    // Set array size
    const int size = 1000;

    // Allocate and initialize CPU memory for arrays data
    float *a = (float*)malloc(size * sizeof(float));
    for (int i=0; i<size; i++) {
        a[i] = (float)i;
    }

    // Process the array data on the GPU
    // using OpenACC compute construct with async clause
    #pragma acc kernels loop async
    for (int i=0; i<size; i++) {
        a[i] = a[i] / 2.0;
    }

    // Wait for all async operations to complete
    #pragma acc wait

    // Check the result
    for (int i=0; i<size; i++) {
        if (a[i] != (float)i / 2.0) {
            err = 1;
            break;
        }
    }

    // Deallocate CPU memory
    free(a);

    return err;
}

int main() {
    // Initialize error code to zero
    int err = 0;

    // Perform test1 for a number of times with different seeds
    for (int i=0; i<10; i++) {
        err += test1();
    }

    // Print result
    printf("Test %s\n", err ? "FAILED" : "PASSED");

    return err;
}