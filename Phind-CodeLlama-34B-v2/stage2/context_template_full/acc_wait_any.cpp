#include "acc_testsuite.h"
#ifndef T1
/*T1:acc wait any,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async_queue[2];
    async_queue[0] = acc_async_sync;
    async_queue[1] = acc_async_sync;

    int wait_result = acc_wait_any(2, async_queue);

    if (wait_result != -1) {
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