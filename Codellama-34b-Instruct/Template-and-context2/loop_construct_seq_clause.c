#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    int i, j;
    int N = 100;
    int a[N];
    int b[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Execute loop with seq clause
    #pragma acc parallel loop seq
    for (i = 0; i < N; i++) {
        b[i] = a[i];
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            err++;
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