#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int a[N];
    int b[N];

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Collapse loops
    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i] += b[j];
        }
    }

    // Check results
    for (int i = 0; i < N; i++) {
        if (a[i] != N * (N + 1) / 2) {
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