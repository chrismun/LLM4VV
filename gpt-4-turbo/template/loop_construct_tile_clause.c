#include "acc_testsuite.h"
#ifndef T1
//T1: loop,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int n = 100; // Define matrix size.
    float a[n][n], b[n][n], c[n][n];
    float seq_c[n][n];

    // Initialize matrices.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() / (float)RAND_MAX;
            b[i][j] = rand() / (float)RAND_MAX;
            seq_c[i][j] = a[i][j] + b[i][j]; // Calculate result in a serial manner for validation.
        }
    }

    // Perform parallel matrix addition using the tile clause.
    #pragma acc parallel loop tile(32,32)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }

    // Check for errors.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(c[i][j] - seq_c[i][j]) > 1e-5) {
                err++;
            }
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