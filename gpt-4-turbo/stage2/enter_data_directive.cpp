#include <iostream>
#include <stdlib.h>
#include <openacc.h> // Make sure openacc.h is available for OpenACC directives.

// Assuming acc_testsuite.h is part of your testing framework
#include "acc_testsuite.h"

#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int size = 100;
    int *a = new int[size];

    // Initialize array
    for(int i = 0; i < size; ++i) {
        a[i] = rand() % 100; // Random values between 0 and 99
    }
    
    // Enter data into device
    #pragma acc enter data copyin(a[0:size])

    // Perform operation on device to validate data has been entered
    #pragma acc parallel loop present(a[0:size])
    for(int i = 0; i < size; ++i) {
        a[i] += 1; // Increment each element to check for transferred data
    }

    // Exit data from device
    #pragma acc exit data copyout(a[0:size])

    // Validate if data was correctly manipulated
    for(int i = 0; i < size; ++i) {
        if(a[i] % 101 != 0) { // Considering original values are between 0 to 99 and incremented once
            err++;
        }
    }

    delete[] a; // Cleanup
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}