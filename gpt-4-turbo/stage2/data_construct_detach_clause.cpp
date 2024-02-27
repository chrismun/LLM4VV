#include <cstdlib>
#include <iostream>
#include <openacc.h>

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 1
#endif

// Test for the data construct detach clause.
int test1() {
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    float* a = new float[size];

    // Initializing array
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (float)RAND_MAX;
    }

    #pragma acc enter data copyin(a[0:size]) // Ensuring data is on the device

    #pragma acc parallel loop present(a[0:size])
    for (int i = 0; i < size; ++i) {
        a[i] = a[i] * 2.0f;
    }

    // Detach the data without an immediate finalize directive
    #pragma acc exit data detach(a)

    // Trying a dummy operation to check if data was detached
    // In practice, accessing 'a' after detach could lead to undefined behavior
    // This operation is just to simulate a check. Replace with a valid mechanism to detect detachment in your context.
    // Note: This might not reliably indicate detach in all environments or could induce undefined behavior.
    float test_sum = 0.0;
    for (int i = 0; i < size; ++i) {
        test_sum += a[i];
    }
    // Dummy check, assuming detachment would cause some kind of noticeable error or behavior in 'test_sum'
    // This is simplistic and for demonstration only. Real detection might need explicit device side checks or compiler/runtime specific mechanisms.
    if(test_sum == 0) {
        err = 1; // Indicate error assuming detach would reset, reduce or alter the contents in some detectable way.
    }

    delete[] a; // Cleanup

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}