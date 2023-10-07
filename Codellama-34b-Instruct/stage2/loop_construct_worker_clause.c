#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set up the parallel region
    #pragma acc parallel num_workers(4)
    {
        // Set up the loop construct
        #pragma acc loop worker
        for (int i = 0; i < 10; i++) {
            // Do some work
            #pragma acc atomic update
            int x = i;
            #pragma acc atomic update
            int y = i;
        }
    }

    // Check that the loop iterations were executed in parallel
    for (int i = 0; i < 10; i++) {
        if (x[i] != y[i]) {
            err = 1;
            break;
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