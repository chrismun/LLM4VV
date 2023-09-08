#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the data
    int N = 100;
    int a[N];
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Collapse the loops
#pragma acc parallel loop collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i] += a[j];
        }
    }

    // Check the result
    for (int i = 0; i < N; i++) {
        if (a[i] != (i * (i + 1)) / 2) {
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