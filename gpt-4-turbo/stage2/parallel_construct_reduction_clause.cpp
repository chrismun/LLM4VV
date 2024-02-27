#include <iostream>
#include <stdlib.h> // For srand, rand
#include <openacc.h> // For OpenACC API

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// Assuming acc_testsuite.h has the necessary setup for OpenACC tests.
#include "acc_testsuite.h"

#ifndef T1
// T1:parallel construct reduction clause, V:2.7-3.3
// This test verifies if the OpenACC parallel reduction clause sums up array elements correctly.
int test1() {
    int err = 0;
    const int size = 1000;
    int data[size];
    int sum = 0;
    int expected_sum = 0;

    srand(SEED);

    // Initialize data and compute expected sum.
    for (int i = 0; i < size; i++) {
        data[i] = rand() % 100;  // Keep data range manageable.
        expected_sum += data[i];
    }

    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += data[i];
    }

    if (sum != expected_sum) {
        std::cerr << "Mismatch: sum is " << sum << ", expected " << expected_sum << std::endl;
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
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