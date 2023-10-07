#include <iostream>
#include <cstdlib>
#include <cmath>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize the vector length
    int vector_length = 4;

    // Initialize the loop counter
    int i = 0;

    // Loop over the vector length
    for (i = 0; i < vector_length; i++) {
        // Perform some computation
        int result = i * i;

        // Check if the result is correct
        if (result != i * i) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}