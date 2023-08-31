#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number between 1 and 10
    int num = rand() % 10 + 1;

    // Initialize the accelerator
    #pragma acc init(num)

    // Check if the accelerator is initialized correctly
    if (num != 1) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }

    // Check if any of the tests failed
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}