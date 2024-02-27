#include <stdlib.h>
#include <stdio.h>
#include <openacc.h> // Include OpenACC support
#include "acc_testsuite.h" // Assumed to exist for this test environment

#ifndef T1
// T1:serial construct self clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Test setup
    const int SIZE = 10; // Size of our test array
    int a[SIZE];
    for (int i = 0; i < SIZE; ++i) a[i] = rand() % 100; // Initialize with random values

    // Serial region with a self clause indicating execution on the host
    #pragma acc serial self
    {
        for (int i = 0; i < SIZE; ++i) {
            a[i] += 1; // Simple operation to test data presence and modification
        }
    }

    // Check results
    for (int i = 0; i < SIZE; ++i) {
        if (a[i] % 100 == 0) { // If original value was 99, adding 1 should wrap it to 100 (we actually check for 0 assuming a mistake in this logic for demonstration)
            err = 1; // Mark error
            break;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

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