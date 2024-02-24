#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int async = acc_async_sync;
    int wait_arg = acc_async_sync;

    #pragma acc enter data copyin(wait_arg)
    #pragma acc enter data copyin(async)

    #pragma acc parallel async(async)
    {
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 1000000; i++){
            // Do some work
        }
    }

    #pragma acc wait(wait_arg)

    #pragma acc exit data delete(wait_arg)
    #pragma acc exit data delete(async)

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