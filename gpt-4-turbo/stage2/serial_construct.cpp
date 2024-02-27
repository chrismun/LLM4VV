#include <iostream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time(), to seed the random number generator

// Assuming acc_testsuite.h defines constants and utility functions for the test suite
#include "acc_testsuite.h" 

#ifndef T1
// T1:serial construct, V:2.7-3.3
int test1() {
    int err = 0; // Error flag
    srand(SEED);

    const int N = 100; // Size of the vectors
    std::vector<int> a(N), b(N), c(N);

    // Initialize vectors
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100; // Random number between 0 and 99
        b[i] = rand() % 100;
    }

    // OpenACC Serial region to perform vector addition
    #pragma acc serial
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Verification
    for(int i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            err++;
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}