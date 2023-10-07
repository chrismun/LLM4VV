#include <iostream>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// Test1: parallel construct, Version: 2.0-2.7
int test1() {
    int err = 0;
    const int N = 100;
    int A[N];
    srand(SEED);

    #pragma acc parallel loop
    for(int i=0; i<N; i++) {
        A[i] = i;
    }

    // Verification part, check if all elements are as expected
    for(int i=0; i<N; i++) {
        if(A[i] != i) {
            err = 1;
            break;
        }
    }
    return err;
}
#endif

int main() {
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