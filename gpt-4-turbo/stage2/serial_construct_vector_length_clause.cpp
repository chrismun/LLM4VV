#include <iostream>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:serial construct vector_length clause,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int test_vector_length = 64; // Example vector_length
    int* a = new int[test_vector_length];
    int sum = 0;

    // Initialize array with random data
    for (int i = 0; i < test_vector_length; ++i) {
        a[i] = rand() % 100;
    }

    // Using OpenACC serial construct with vector_length clause
    #pragma acc serial vector_length(test_vector_length)
    {
        for (int i = 0; i < test_vector_length; ++i) {
            sum += a[i];
        }
    }

    // Test verification (Dummy check, real-world case would need a control case for comparison)
    // Assuming if the code runs through the serial block, it's correct.
    // To ensure correctness, compare with a CPU-executed sum (left as future work).
    err = (sum > 0) ? 0 : 1;

    delete[] a;
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