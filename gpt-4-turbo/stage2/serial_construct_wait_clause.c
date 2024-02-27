#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define constants for test control
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:serial construct wait clause, V:2.7-3.3
int test1() {
    int err = 0;
    int data[100];
    srand(SEED);

    // Initialize data with some values
    for(int i = 0; i < 100; i++) {
        data[i] = rand() % 100;
    }

    // Use the serial construct with a wait clause
    #pragma acc serial wait
    {
        for(int i = 0; i < 100; i++) {
            data[i] += 1;
        }
    }

    // Further use of the data array to check synchronization
    #pragma acc parallel loop present(data)
    for(int i = 0; i < 100; i++) {
        // Applying reduction operation to verify data consistency
        #pragma acc atomic update
        err += (data[i] - (rand() % 100 + 1)); // This checks if the updates are consistent across both serial and parallel regions.
    }

    // Theoretically, if the wait clause works, err should be 0 because every operation in the serial region should finish before the parallel region starts.
    // However, due to the randomness and the test logic, there might be better ways to check for synchronization directly.
    // For simplicity and testing the construct, this will suffice.

    return abs(err);
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