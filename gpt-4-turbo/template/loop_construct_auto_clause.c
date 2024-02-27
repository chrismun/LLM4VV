#include "acc_testsuite.h"
#ifndef T1
//T1:{loop},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int n = 1000;
    int a[n], sum = 0, computed_sum = 0;

    // Initialize array with random numbers and compute the expected sum
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 100; // Values between 0 and 99
        sum += a[i];
    }

    // Compute the sum using OpenACC parallel loop with auto clause
    #pragma acc parallel loop auto
    for (int i = 0; i < n; ++i) {
        #pragma acc atomic
        computed_sum += a[i];
    }

    // Check if the computed sum is as expected
    if (computed_sum != sum) {
        err = 1;
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}