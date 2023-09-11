#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default clause to "parallel"
    acc_set_default_clause(ACC_PARALLEL);

    // Create a parallel region with the default clause
    #pragma acc parallel
    {
        // Do some work in the parallel region
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // ...
        }
    }

    // Check that the default clause was applied correctly
    if (acc_get_default_clause() != ACC_PARALLEL) {
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