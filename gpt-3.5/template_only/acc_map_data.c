#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int n = 1000;
    int *A = (int*)malloc(n * sizeof(int));
    int *A_copy = (int*)malloc(n * sizeof(int));

    // Initialize data
    for(int i = 0; i < n; i++){
        A[i] = rand() % 100;
        A_copy[i] = A[i];
    }

    #pragma acc data copy(A[0:n]) map(tofrom: A_copy[0:n])
    {
        #pragma acc parallel loop
        for(int i = 0; i < n; i++){
            A_copy[i] += 1;
        }
    }

    // Verify the result
    for(int i = 0; i < n; i++){
        if(A_copy[i] != (A[i] + 1)){
            err = 1;
            break;
        }
    }

    free(A);
    free(A_copy);

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