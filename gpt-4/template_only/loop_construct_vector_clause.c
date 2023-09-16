#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    int size = 100;
    int A[size][size], B[size][size], C[size][size];

    // Initialize matrices A and B
    srand(SEED);
    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++) {
            A[i][j] = rand()%1000;
            B[i][j] = rand()%1000;
        }

    // Perform matrix multiplication using OpenACC
#pragma acc parallel loop collapse(2)
    for (int i=0; i<size; i++)
        for (int j=0; j<size; j++) {
            C[i][j] = 0;
            // Matrix Multiplication
#pragma acc loop vector
            for (int k=0; k<size; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    // Validate the result
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            int temp = 0;
            for (int k=0; k<size; k++)
                temp += A[i][k] * B[k][j];
            if (C[i][j] != temp) {
                err = 1;
                break;
            }
        }
        if (err == 1)
            break;
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