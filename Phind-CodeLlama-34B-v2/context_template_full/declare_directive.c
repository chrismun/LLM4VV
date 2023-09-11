#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define NUM_TEST_CALLS 1

#ifndef T1
/*T1:declare directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int N = 1024;
    int *a = (int *)malloc(N * sizeof(int));
    int *d_a = (int *)acc_malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    #pragma acc declare create(d_a[0:N])
    #pragma acc parallel present(d_a[0:N])
    {
        int idx = acc_thread_id();
        d_a[idx] = a[idx];
    }

    #pragma acc update host(d_a[0:N])

    for (int i = 0; i < N; i++) {
        if (a[i] != d_a[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    acc_free(d_a);

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