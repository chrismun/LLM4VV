#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    
    int A[N], B[N], C[N], scalar;

    // Initialize arrays
    for (int i = 0; i < N; ++i){
        A[i] = rand() % 100;
        B[i] = rand() % 100;
    }  
    
    // Predetermined data attribute
    #pragma acc data copyin(A[0:N], B[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i){
            C[i] = A[i] + B[i];
        }
    }

    // Verify the results
    for (int i = 0; i < N; ++i){
        if (C[i] != A[i] + B[i]){
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
    
    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}