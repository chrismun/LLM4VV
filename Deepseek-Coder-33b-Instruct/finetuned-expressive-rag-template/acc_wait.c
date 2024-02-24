#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // create an asynchronous operation
    acc_async_test();

    // wait for the asynchronous operation to complete
    acc_wait(0);

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