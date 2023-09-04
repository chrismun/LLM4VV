#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#define SEED 123456789
#define NUM_TEST_CALLS 1000

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random number between 1 and 100
    int x = rand() % 100 + 1;

    // Generate a random number between 1 and 100
    int y = rand() % 100 + 1;

    // Calculate the sum of x and y
    int sum = x + y;

    // Check if the sum is equal to the expected result
    if (sum != x + y) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 1000 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode != 0) {
        printf("Failed: %d\n", failcode);
    } else {
        printf("Passed\n");
    }

    return 0;
}