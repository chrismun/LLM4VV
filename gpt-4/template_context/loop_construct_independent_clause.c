#include "acc_testsuite.h"

// T1:loop construct independent clause,V:2.7-3.3
int test1(){
    int dataSize = 1024;
    int *A = (int*)malloc(dataSize*sizeof(int));
    int *B = (int*)malloc(dataSize*sizeof(int));
    int err = 0;

    // initialize data
    srand(SEED);
    for (int i = 0; i < dataSize; i++) {
        A[i] = rand() % 1024;
        B[i] = 0;
    }

#pragma acc data copyin(A[0:dataSize]) copyout(B[0:dataSize])
    {
#pragma acc parallel loop independent
        for (int i = 0; i < dataSize; i++) {
            B[i] = A[i]*2;
        }
    }

    for (int i = 0; i < dataSize; i++){
        if (B[i] != A[i]*2){
            err = 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
        
    return failcode;
}