#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a[100];
    int b[100];
    int c[100];

    #pragma acc parallel loop reduction(+:a[0:100])
    for (int i = 0; i < 100; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop reduction(*:b[0:100])
    for (int i = 0; i < 100; i++) {
        b[i] = i;
    }

    #pragma acc parallel loop reduction(max:c[0:100])
    for (int i = 0; i < 100; i++) {
        c[i] = i;
    }

    #pragma acc parallel loop reduction(min:c[0:100])
    for (int i = 0; i < 100; i++) {
        c[i] = i;
    }

    #pragma acc parallel loop reduction(&:a[0:100])
    for (int i = 0; i < 100; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop reduction(|:b[0:100])
    for (int i = 0; i < 100; i++) {
        b[i] = i;
    }

    #pragma acc parallel loop reduction(^:c[0:100])
    for (int i = 0; i < 100; i++) {
        c[i] = i;
    }

    #pragma acc parallel loop reduction(&&:a[0:100])
    for (int i = 0; i < 100; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop reduction(||:b[0:100])
    for (int i = 0; i < 100; i++) {
        b[i] = i;
    }

    #pragma acc parallel loop reduction(eqv:c[0:100])
    for (int i = 0; i < 100; i++) {
        c[i] = i;
    }

    #pragma acc parallel loop reduction(neqv:c[0:100])
    for (int i = 0; i < 100; i++) {
        c[i] = i;
    }

    return 0;
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