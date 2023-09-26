#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 123
#define RAND_MAX 1000
#define PRECISION 0.001

int test_acc_async_test(){
    int err = 0;
    int n = 1024;
    int async_queue = 1;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for(int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n]) async(async_queue)
    {
        #pragma acc kernels async(async_queue)
        {
            #pragma acc loop
            for(int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }
    }

    #pragma acc wait(async_queue)

    for(int x = 0; x < n; ++x){
        if(fabs(b[x] - a[x]) > PRECISION){
            err += 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for(int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_async_test();
    }
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}