#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a[100];
    int b[100];
    int c[100];

    // Initialize arrays
    for (int i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // Perform reduction
    #pragma acc parallel loop reduction(+:c)
    for (int i = 0; i < 100; i++) {
        c[i] += a[i] + b[i];
    }

    // Check results
    for (int i = 0; i < 100; i++) {
        if (c[i] != (a[i] + b[i])) {
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