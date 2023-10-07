#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:update directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    const int N = 1024;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    for (int x = 0; x < N; ++x){
        a[x] = rand() % 256;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc parallel present(a[0:N], b[0:N])
    {
        int idx = acc_thread_id();
        b[idx] = a[idx] * 2;
    }

    #pragma acc update host(b[0:N])

    for (int x = 0; x < N; ++x){
        if (b[x] != a[x] * 2){
            err = 1;
            break;
        }
    }

    #pragma acc exit data delete(a[0:N])
    #pragma acc exit data delete(b[0:N])

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