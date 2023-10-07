#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc parallel copy(a[0:N]) copyout(b[0:N])
    {
        int idx = acc_global_thread_id();
        if (idx < N) {
            b[idx] = a[idx] + 5;
        }
    }

    for (int i = 0; i < N; i++) {
        if (b[i] != a[i] + 5) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}