#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10
#define N 100

#ifndef T1
// T1:{loop,private}, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int a[N][N][N], b[N][N], c[N][N];
    int div = 2;
    // Initialize arrays b and c
    for (int k = 0; k < N; ++k) {
        for (int j = 0; j < N; ++j) {
            b[j][k] = rand() % 10;
            c[j][k] = rand() % 10;
        }
    }

    #pragma acc parallel num_gangs(1)
    {
        #pragma acc loop gang
        for (int k = 0; k < N; k++) {
            #pragma acc loop worker private(tmp)
            for (int j = 0; j < N; j++) {
                int tmp = b[j][k] + c[j][k]; // Make tmp private to each worker
                #pragma acc loop vector
                for (int i = 0; i < N; i++) {
                    a[i][j][k] = tmp / div; // Use tmp which should be private to this worker
                }
            }
        }
    }

    // Verify that the operation was done correctly, assuming private worked as expected
    for (int k = 0; k < N && err == 0; ++k) {
        for (int j = 0; j < N && err == 0; ++j) {
            int expected = (b[j][k] + c[j][k]) / div;
            for (int i = 0; i < N && err == 0; i++) {
                if (a[i][j][k] != expected) {
                    err = 1; // Error if the result doesn't match expected, implying a private clause issue
                }
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    #endif
    printf("Test %s\n", failcode ? "FAILED" : "PASSED");
    return failcode;
}