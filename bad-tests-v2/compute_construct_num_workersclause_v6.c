#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the number of workers to 4
    #pragma acc parallel num_workers(4)
    {
        // Do some work
        #pragma acc loop
        for (int i = 0; i < 100; i++) {
            // ...
        }
    }

    // Check that the number of workers is 4
    if (acc_get_num_workers() != 4) {
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