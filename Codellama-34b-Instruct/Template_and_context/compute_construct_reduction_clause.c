#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int a[n];
    int b[n];
    int c[n];

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = i;
    }

    #pragma acc parallel loop reduction(+:a,b,c)
    for (int i = 0; i < n; i++) {
        a[i] += b[i];
        b[i] += c[i];
        c[i] += a[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i] || b[i] != c[i] || c[i] != a[i]) {
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