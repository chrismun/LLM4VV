#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a vector of random numbers
    std::vector<int> vec(100);
    for (int i = 0; i < vec.size(); i++) {
        vec[i] = rand() % 100;
    }

    // Create a compute region with a loop directive
    #pragma acc parallel loop
    for (int i = 0; i < vec.size(); i++) {
        // Create a private variable for each thread
        int private_var = vec[i];

        // Perform some computation on the private variable
        private_var = private_var * 2;

        // Check that the private variable is still the same as the original value
        if (private_var != vec[i]) {
            err = 1;
            break;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Return the failcode if any of the tests failed
    return failcode;
}