#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int i, j;
    int a[100];
    int b[100];

    #pragma acc parallel loop seq
    for (i = 0; i < 100; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop seq
    for (j = 0; j < 100; j++) {
        b[j] = j;
    }

    for (i = 0; i < 100; i++) {
        if (a[i] != b[i]) {
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