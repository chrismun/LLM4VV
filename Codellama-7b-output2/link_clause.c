#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int data1 = rand() % 100;
    int data2 = rand() % 100;

    // Create a link clause
    #pragma acc link(data1, data2)

    // Verify that the link clause is working properly
    if (data1 != data2) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure that the link clause is working properly
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }

    // Check if any of the tests failed
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}