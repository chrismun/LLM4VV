#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1: loop construct auto clause, V: 2.7-3.3
int test1() {
    int err = 0;
    const int n = 10000;
    float a[n], b[n], c[n];
    srand(SEED);

    // Initialize arrays with random values
    for (int i = 0; i < n; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }
    
    #pragma acc kernels
    {
        #pragma acc loop auto
        for (int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Validation step - Ideally done on the host to ensure ACC execution
    for (int i = 0; i < n; i++) {
        if (abs((a[i] + b[i]) - c[i]) > 0.00001) { // Simple floating-point comparison
            err++;
        }
    }

    return err; // 0 errors implies successful parallel execution under the assumption of data independence validation by the compiler
}

int main() {
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
    if (failcode == 0) {
        printf("PASS: Loop construct auto clause test passed.\n");
    } else {
        printf("FAIL: Loop construct auto clause test failed.\n");
    }
    return failcode;
}