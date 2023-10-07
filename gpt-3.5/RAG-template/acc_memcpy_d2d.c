#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int *A, *B, *C;
    int nbytes = N * sizeof(int);

    A = (int*)malloc(nbytes);
    B = (int*)malloc(nbytes);
    C = (int*)malloc(nbytes);

    srand(SEED);

    for (int i = 0; i < N; i++){
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }

    #pragma acc data copyin(A[0:N]) copyout(C[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++){
            C[i] = A[i] + B[i];
        }
    }

    for (int i = 0; i < N; i++){
        if (C[i] != A[i] + B[i]){
            err = 1;
            break;
        }
    }

    free(A);
    free(B);
    free(C);

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