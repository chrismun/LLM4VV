#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,data,exit-data,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x] + 1; // Initialize differently to ensure deletion takes effect
    }

    #pragma acc enter data copyin(a[0:n], b[0:n])
    #pragma acc parallel loop present(a[0:n], b[0:n])
    for (int x = 0; x < n; ++x){
        b[x] = a[x]; // Use data in some computation to justify the copyin
    }

    // Here we perform deletion. According to the specification, if a variable is referenced, it's detached or its counter updated.
    #pragma acc exit data delete(a[0:n])

    // To validate, we check if 'a' behaves as though it no longer resides in the device memory by performing an operation that should not reflect on the device
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10); // This change should not reflect on the device version of 'a'
    }

    // Dummy copyout operation to check if 'a' has been truly detached/deleted.
    #pragma acc update host(b[0:n]) // Update host with the latest device data

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) <= PRECISION){ // Since 'a' is modified and 'b' is updated from the device, their difference should be significant if delete worked.
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int error_code = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if (test1() != 0) {
            failed = 1;
        }
    }
    if (failed) {
        error_code += 1;
    }
#endif

    if (error_code) {
        printf("Test FAILED\n");
    } else {
        printf("Test PASSED\n");
    }
    return error_code;
}