#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a[10];
    int b[10];
    int c[10];

    #pragma acc parallel loop reduction(+:a[0:10])
    for (int i = 0; i < 10; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop reduction(+:b[0:10])
    for (int i = 0; i < 10; i++) {
        b[i] = i;
    }

    #pragma acc parallel loop reduction(+:c[0:10])
    for (int i = 0; i < 10; i++) {
        c[i] = i;
    }

    #pragma acc parallel loop reduction(+:a[0:10], b[0:10], c[0:10])
    for (int i = 0; i < 10; i++) {
        a[i] += b[i] + c[i];
    }

    if (a[0] != 30 || a[1] != 30 || a[2] != 30 || a[3] != 30 || a[4] != 30 || a[5] != 30 || a[6] != 30 || a[7] != 30 || a[8] != 30 || a[9] != 30) {
        err = 1;
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