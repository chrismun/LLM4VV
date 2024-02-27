#include <iostream>
#include <stdlib.h> // For rand(), srand()
#include <openacc.h> // For acc_malloc and acc_free

// Dummy acc_testsuite.h as a placeholder for necessary constants and the test environment setup.
// Replace this with your actual setup header or define SEED and NUM_TEST_CALLS appropriately.
#include "acc_testsuite.h"

#ifndef T1
// T1: acc_malloc, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int test_size = rand() % 1024 + 1; // Ensure non-zero size

    // Attempt to allocate device memory
    void* device_ptr = acc_malloc(test_size);
    if (device_ptr == nullptr) {
        std::cerr << "acc_malloc failed to allocate device memory.\n";
        err++;
    } else {
        // If allocation succeeded, attempt to free the allocated memory
        acc_free(device_ptr);
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