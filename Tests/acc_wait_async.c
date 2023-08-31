#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number between 1 and 10
    int x = rand() % 10 + 1;

    // Create a buffer to store the result of the async operation
    int result = 0;

    // Launch an async operation that will take x seconds to complete
    #pragma acc parallel async(x)
    {
        // Simulate a long-running operation
        for (int i = 0; i < 1000000; i++) {
            result = i;
        }
    }

    // Wait for the async operation to complete
    #pragma acc wait(x)

    // Check if the result is correct
    if (result != x) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure that the compiler is consistent
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}