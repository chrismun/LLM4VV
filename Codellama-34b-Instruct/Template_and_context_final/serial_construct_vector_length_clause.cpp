#include <iostream>
#include <cstdlib>
#include <cmath>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random vector length
    int vector_length = rand() % 10 + 1;

    // Create a serial construct with the vector_length clause
    #pragma acc serial vector_length(vector_length)
    {
        // Perform some vector operations
        float a[vector_length];
        float b[vector_length];
        for (int i = 0; i < vector_length; i++) {
            a[i] = i;
            b[i] = i * 2;
        }
        for (int i = 0; i < vector_length; i++) {
            a[i] += b[i];
        }
    }

    // Check the results
    for (int i = 0; i < vector_length; i++) {
        if (a[i] != i * 3) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}