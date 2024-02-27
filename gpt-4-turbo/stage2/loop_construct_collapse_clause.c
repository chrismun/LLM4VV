#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1: loop construct collapse clause, V:2.7-3.3
int test1() {
    int err = 0;

    // Assuming 100x100 matrix for a simple test
    const int N = 100;
    int matrix[N][N];

    // Initialize matrix to zeros
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = 0;
        }
    }

    // Using OpenACC to parallelize and collapse loops
    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = i + j;
        }
    }

    // Verify all values are correctly updated
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j] != i + j) {
                err++;
            }
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}