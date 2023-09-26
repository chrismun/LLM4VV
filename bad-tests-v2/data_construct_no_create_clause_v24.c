#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    
    int n = 100;
    int *A = (int *)malloc(n * sizeof(int));
    int *B = (int *)malloc(n * sizeof(int));
    
    // Initialize arrays A and B
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }
    
    #pragma acc data copyin(A[0:n]) no_create(B[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            B[i] = B[i] + A[i];
        }
    }
    
    // Verify the result
    for (int i = 0; i < n; i++) {
        if (B[i] != 2 * A[i]) {
            err = 1;
            break;
        }
    }
    
    free(A);
    free(B);

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