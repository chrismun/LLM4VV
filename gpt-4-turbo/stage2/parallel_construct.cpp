#include <iostream>
#include <cstdlib>
#include <cmath>
#include <openacc.h>

#ifndef T1
// T1:parallel construct, V:2.7-3.3
int test1() {
    int err = 0;
    const int size = 1024;
    float a[size], sum = 0.0, expected_sum = 0.0;

    srand(42); // Initialize random seed

    for(int i = 0; i < size; i++) {
        a[i] = static_cast<float>(rand()) / RAND_MAX; // Assign random values
        expected_sum += a[i];
    }

    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < size; i++) {
        sum += a[i];
    }

    if(std::fabs(sum - expected_sum) > 0.001) { // simple error check
        err = 1;
    }

    return err;
}
#endif

int main() {
    const int NUM_TEST_CALLS = 10;
    int failcode = 0;
    int failed = 0;

#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    // In a proper test suite, you might have detailed error messages indicating the type of failure.
    if (failcode) {
        std::cerr << "Test failed with error code: " << failcode << std::endl;
    } else {
        std::cout << "All tests passed successfully." << std::endl;
    }

    return failcode;
}