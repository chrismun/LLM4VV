#include "acc_testsuite.h"

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with a loop inside
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        // Create a serial region with a loop inside
        #pragma acc serial loop
        for (int j = 0; j < 10; j++) {
            // Create a kernels region with a loop inside
            #pragma acc kernels loop
            for (int k = 0; k < 10; k++) {
                // Do some work
            }
        }
    }

    // Check that the combined constructs were executed correctly
    if (/* check that the loops were executed correctly */) {
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