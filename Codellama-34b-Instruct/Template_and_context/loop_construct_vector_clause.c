#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set up the loop
    int i, j;
    int N = 100;
    int M = 10;
    int A[N][M];
    int B[N][M];
    int C[N][M];

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }

    // Set up the vector clause
    int vector_length = 4;
    int vector_stride = 1;
    int vector_offset = 0;

    // Execute the loop with vector processing
    #pragma acc parallel loop vector(vector_length, vector_stride, vector_offset)
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Check the results
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (C[i][j] != A[i][j] + B[i][j]) {
                err = 1;
                break;
            }
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}