#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the loop construct with the worker clause
    #pragma acc loop worker
    for (int i = 0; i < 10; i++) {
        // Do some work here
    }

    // Check that the loop iterations were distributed among the workers
    for (int i = 0; i < 10; i++) {
        if (acc_get_worker_id() != i) {
            err++;
        }
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