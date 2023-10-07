#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int a[n];
    int b[n];
    int c[n];
    int tmp[n];

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
        tmp[i] = 0;
    }

    // Compute the sum of a and b, and store the result in tmp
    #pragma acc parallel loop gang(static:1) private(tmp)
    for (int i = 0; i < n; i++) {
        tmp[i] = a[i] + b[i];
    }

    // Compute the sum of tmp and c, and store the result in a
    #pragma acc parallel loop gang(static:1) private(tmp)
    for (int i = 0; i < n; i++) {
        a[i] = tmp[i] + c[i];
    }

    // Check the result
    for (int i = 0; i < n; i++) {
        if (a[i] != (i + i + i)) {
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