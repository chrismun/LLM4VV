#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:parallel construct default clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(2023); // Using a fixed seed for reproducibility

    int data = 5; // Test data

    // Using default(shared) to denote that variables in the parallel region
    // are shared by default unless explicitly stated otherwise.
    #pragma acc parallel default(shared)
    {
        data += 5; // Modify the shared variable in the parallel region
    } // Implicit barrier here ensures 'data' is updated once all threads complete execution

    // The correct updated value should be 10 if the default(shared) clause worked as expected
    if(data != 10) {
        err = 1; // Set error if the value wasn't updated correctly
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < 1; ++x) { // Assuming NUM_TEST_CALLS = 1 for simplicity
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}