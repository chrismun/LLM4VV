#include "acc_testsuite.h"
#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop gang vector
    for (int i = 0; i < N; i++) {
        #pragma acc loop gang vector
        for (int j = 0; j < M; j++) {
            // Combined construct: Data and compute regions
            #pragma acc data present(A, B) copyout(C)
            {
                #pragma acc loop
                for (int k = 0; k < P; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    // Verify the correctness of the computation
    int correct = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int sum = 0;
            for (int k = 0; k < P; k++) {
                sum += A[i][k] * B[k][j];
            }
            if (C[i][j] != sum) {
                correct = 0;
                break;
            }
        }
        if (!correct) {
            break;
        }
    }

    if (!correct) {
        err = 1;
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