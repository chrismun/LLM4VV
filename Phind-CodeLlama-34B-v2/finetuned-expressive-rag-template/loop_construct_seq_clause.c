#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 100000;
    int a[N], b[N], c[N];

    for (int i = 0; i < N; i++) {
        a[i] = rand() % N;
        b[i] = rand() % N;
    }

    #pragma acc data copy(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc kernels loop seq
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
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