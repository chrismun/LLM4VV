#include "acc_testsuite.h"
#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Define arrays A and B
    int n = 100;
    int *A = (int *)malloc(n * sizeof(int));
    int *B = (int *)malloc(n * sizeof(int));

    // Initialize arrays A and B
    for (int i = 0; i < n; i++) {
        A[i] = 0;
        B[i] = 1;
    }

    // Check if arrays A and B are initialized correctly
    for (int i = 0; i < n; i++) {
        if (A[i] != 0 || B[i] != 1) {
            err = 1;
            break;
        }
    }

    // Delete data clause for array B
    #pragma acc data delete(B)

    // Check if B is deleted correctly
    for (int i = 0; i < n; i++) {
        if (B[i] != 1) {
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