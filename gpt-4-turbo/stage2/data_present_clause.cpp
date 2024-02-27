#include <iostream>
#include <openacc.h>
#include <stdlib.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Prototype of our test function
int test_data_present_clause();

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_data_present_clause();
    }
    if (failed != 0){
        failcode += 1;
    }
    return failcode;
}

int test_data_present_clause() {
    int err = 0;
    srand(SEED);

    const int size = 1024;
    double* a = (double*)malloc(size * sizeof(double));

    // Initialize array
    for (int i = 0; i < size; i++) {
        a[i] = rand() / (double)RAND_MAX;
    }

    // Ensure the data is present on the device
    #pragma acc enter data create(a[0:size])

    // Trying to use data that must be present on the device.
    #pragma acc parallel loop present(a[0:size])
    for (int i = 0; i < size; i++) {
        a[i] = a[i] * 2.0;
    }

    // Dummy check to ensure data has been modified (in a real case, we would copy back and check on the host)
    #pragma acc parallel loop present(a[0:size]) reduction(+:err)
    for (int i = 0; i < size; i++) {
        if (a[i] != 2.0 * (a[i] / 2.0)) { // After doubling, this check should always pass
            err++;
        }
    }

    // Cleanup device memory
    #pragma acc exit data delete(a[0:size])

    free(a); // Free host memory

    return err; // Returns 0 if no errors, >0 if errors detected
}