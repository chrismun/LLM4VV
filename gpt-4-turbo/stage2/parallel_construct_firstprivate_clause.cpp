#include <iostream>
#include <stdlib.h>
#include <openacc.h> // Ensure this header is available in your compiler for OpenACC support

// Fictive acc_test_suite.h for OpenACC tests
// Typically, in a real environment, this would include necessary test configurations
#include "acc_testsuite.h"

#ifndef T1
// T1: parallel construct firstprivate clause, Version 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    const int size = 100;
    int initial_value = rand() % 100; // Random initial value
    int results[size];

    // Initialize array with zeros
    for (int i = 0; i < size; ++i) {
        results[i] = 0;
    }

    #pragma acc parallel num_gangs(1) vector_length(size) copyout(results[0:size]) firstprivate(initial_value)
    {
        int gang_id = acc_get_gang_num();
        int vector_id = acc_get_thread_num();

        // Assign initial_value (which should be private to each vector) to results
        results[vector_id] = initial_value;
    }

    // Check results
    for (int i = 0; i < size; ++i) {
        if (results[i] != initial_value) {
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