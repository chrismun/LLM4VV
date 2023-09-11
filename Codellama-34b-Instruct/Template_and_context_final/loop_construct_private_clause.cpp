#include <iostream>
#include <cstdlib>
#include <cmath>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Initialize variables
    int n = 100;
    int k = 0;
    int j = 0;
    int i = 0;
    int tmp = 0;
    int a[n][n][n];
    int b[n][n];
    int c[n][n];

    // Set up the loop construct
    #pragma acc loop gang(dim:3)
    for (k = 0; k < n; k++) {
        #pragma acc loop worker private(tmp)
        for (j = 0; j < n; j++) {
            tmp = b[j][k] + c[j][k];
            #pragma acc loop vector
            for (i = 0; i < n; i++) {
                a[i][j][k] = a[i][j][k] + tmp;
            }
        }
    }

    // Check the results
    for (k = 0; k < n; k++) {
        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++) {
                if (a[i][j][k] != b[j][k] + c[j][k]) {
                    err = 1;
                    break;
                }
            }
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}