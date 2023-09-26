#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:acc memcpy from device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int N = 1024;
    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc parallel present(a[0:N], b[0:N])
    {
        int idx = acc_thread_id();
        b[idx] = a[idx];
    }

    #pragma acc update host(b[0:N])

    #pragma acc exit data delete(a[0:N])
    #pragma acc exit data copyout(b[0:N])

    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) {
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