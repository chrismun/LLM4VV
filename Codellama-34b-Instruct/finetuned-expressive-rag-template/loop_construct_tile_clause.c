#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 1024;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    for (int x = 0; x < N; ++x){
        a[x] = rand() % N;
        b[x] = 0;
    }

    #pragma acc data copy(a[0:N]), create(b[0:N])
    {
        #pragma acc kernels loop tile(128)
        for (int x = 0; x < N; ++x){
            b[x] = a[x];
        }
    }

    for (int x = 0; x < N; ++x){
        if (a[x] != b[x]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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