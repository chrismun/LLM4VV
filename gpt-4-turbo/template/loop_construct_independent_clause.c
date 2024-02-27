#include "acc_testsuite.h"
#ifndef T1
// T1:loop,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int N = 1000; // Size of the array
    int a[N]; // Original array
    int results[N]; // Array for results

    // Initialize the array with random values
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100; // random numbers between 0 and 99
    }

    // Compute squares in parallel using OpenACC
    #pragma acc parallel loop copyin(a[0:N]) copyout(results[0:N])
    for (int i = 0; i < N; ++i) {
        results[i] = a[i] * a[i];
    }

    // Check for errors
    for (int i = 0; i < N; ++i) {
        if (results[i] != a[i] * a[i]) {
            err++;
            break;
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}