#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copyout(A[0:N]) create(B[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++){
            A[i] = B[i] + 1;
        }
    }

    #pragma acc unmap(A[:N])
  
    for (int i = 0; i < N; i++){
        if (A[i] != B[i] + 1) {
            err = 1;
            break;
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