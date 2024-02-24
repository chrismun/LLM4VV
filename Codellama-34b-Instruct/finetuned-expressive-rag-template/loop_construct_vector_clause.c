#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 1024;
    const int vector_length = 16;
    int a[N], b[N], c[N];

    for (int x = 0; x < N; ++x){
        a[x] = rand() % N;
        b[x] = rand() % N;
    }

    #pragma acc parallel loop vector(vector_length)
    for (int x = 0; x < N; ++x){
        c[x] = a[x] + b[x];
    }

    for (int x = 0; x < N; ++x){
        if (c[x] != a[x] + b[x]){
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