#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number between 1 and 10
    int async_val = rand() % 10 + 1;

    // Set the default async value to the random number
    #pragma acc set default async(async_val)

    // Check if the default async value is set correctly
    if (omp_get_default_async() != async_val) {
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