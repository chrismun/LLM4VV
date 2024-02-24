#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int async_queue = rand() % 2;
    int async_queue_all = rand() % 2;

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    int async_test_result;

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc kernels async(async_queue)
        {
            for (int x = 0; x < n; ++x){
                a[x] = b[x] + c[x];
            }
        }

        #pragma acc kernels async(async_queue_all)
        {
            for (int x = 0; x < n; ++x){
                a[x] = b[x] - c[x];
            }
        }

        async_test_result = acc_async_test(async_queue);
        if (async_test_result){
            fprintf(stderr, "acc_async_test failed for async_queue %d\n", async_queue);
            err = 1;
        }

        async_test_result = acc_async_test_all();
        if (async_test_result){
            fprintf(stderr, "acc_async_test_all failed\n");
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