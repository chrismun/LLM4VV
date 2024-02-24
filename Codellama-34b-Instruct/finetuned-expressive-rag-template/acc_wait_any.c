#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int async1 = acc_async_noval;
    int async2 = acc_async_noval;
    int async3 = acc_async_noval;

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    int wait_arg[3] = {async1, async2, async3};

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(async1)
        {
            for (int x = 0; x < n; ++x) {
                a[x] = b[x] + c[x];
            }
        }

        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(async2)
        {
            for (int x = 0; x < n; ++x) {
                b[x] = a[x] - c[x];
            }
        }

        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(async3)
        {
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] * b[x];
            }
        }

        int index = acc_wait_any(3, wait_arg);

        if (index < 0 || index > 2) {
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);

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