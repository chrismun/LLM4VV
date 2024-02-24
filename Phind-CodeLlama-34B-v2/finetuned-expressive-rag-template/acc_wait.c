#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int async_arg = rand() % 2;
    acc_init(acc_device_nvidia);

    #pragma acc enter data copyin(async_arg)
    #pragma acc parallel async(async_arg)
    {
        // Do some work
    }

    acc_wait(async_arg);

    #pragma acc exit data delete(async_arg)
    acc_shutdown(acc_device_nvidia);

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