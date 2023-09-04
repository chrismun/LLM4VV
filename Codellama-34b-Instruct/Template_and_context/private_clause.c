#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a[10];
    int b[10];
    int c[10];

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = a[i] + b[i];
        c[i] = c[i] + b[i];
    }

    #pragma acc parallel loop private(a, b, c)
    for (int i = 0; i < 10; i++) {
        a[i] = a[i] + c[i];
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