#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    int async_queue[2];
    async_queue[0] = acc_async_noval;
    async_queue[1] = acc_async_noval;

    int *a = (int *)acc_malloc(256 * sizeof(int));
    int *b = (int *)acc_malloc(256 * sizeof(int));

    #pragma acc data copy(a[0:256], b[0:256])
    {
        #pragma acc parallel present(a[0:256], b[0:256]) async(async_queue[0])
        {
            for (int x = 0; x < 256; ++x){
                a[x] = x * 2;
            }
        }

        #pragma acc parallel present(a[0:256], b[0:256]) async(async_queue[1])
        {
            for (int x = 0; x < 256; ++x){
                b[x] = x * 3;
            }
        }

        int wait_result = acc_wait_any(2, async_queue);
        if (wait_result == -1){
            err = 1;
        }
    }

    acc_free(a);
    acc_free(b);

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