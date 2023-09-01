#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an asynchronous task
    int async_task = 0;
    #pragma acc async async_task
    {
        // Do some work
        #pragma acc loop seq
        for (int i = 0; i < 10; i++){
            printf("Hello from async task %d\n", async_task);
        }
    }

    // Wait for the asynchronous task to complete
    #pragma acc wait(async_task)

    // Check if the asynchronous task completed successfully
    if (async_task != 0){
        err = 1;
    }

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