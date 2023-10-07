#include "acc_testsuite.h"
#ifndef T1
//T1: acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copy(A[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            A[x] = 1;
        }
        acc_attach(A, n * sizeof(int));
    }
    for (int x = 0; x < n; ++x){
        if (A[x] != 1){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
    int * failed_bool = &failed;
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