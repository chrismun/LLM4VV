#include <stdio.h>
#include <stdlib.h>

#define ACC_TESTSUITE_H
#define SEED 123
#define NUM_TEST_CALLS 1

#ifdef ACC_TESTSUITE_H
// Setting up a simplistic scenario for testing OpenACC declare directive.

// Test function for the 'declare' directive with 'copyin' and 'create' clauses
int test1() {
    int err = 0;
    const int size = 100;
    int a[size], b[size], c[size];
    
    // Initializing arrays
    for (int i = 0; i < size; ++i) {
        a[i] = rand() / (RAND_MAX / 100);
        b[i] = rand() / (RAND_MAX / 100);
        c[i] = 0;
    }

    // Declare directive for OpenACC to manage 'a' and 'b' arrays in the device with 'copyin' and 'c' with 'create'
    #pragma acc declare copyin(a,b) create(c)

    #pragma acc parallel loop
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i]; // Simple operation to verify the functionality
    }
    
    // Verifying the result
    for (int i = 0; i < size; ++i) {
        if (c[i] != a[i] + b[i]) {
            err++;
        }
    }

    return err;
}

#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("TEST PASSED\n");
    } else {
        printf("TEST FAILED\n");
    }
    return failcode;
}