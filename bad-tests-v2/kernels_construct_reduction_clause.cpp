#include <iostream>
#include <cstdlib>
#include <cmath>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize variables
    int a = 0;
    int b = 0;
    int c = 0;

    // Define reduction variables
    int sum = 0;
    int product = 1;
    int max = INT_MIN;
    int min = INT_MAX;

    // Define kernel
    #pragma acc kernels reduction(+:sum, product, max, min)
    {
        // Perform reduction operations
        sum += a;
        product *= b;
        max = std::max(max, c);
        min = std::min(min, c);
    }

    // Check results
    if (sum != 0 || product != 1 || max != INT_MIN || min != INT_MAX) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run test1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}