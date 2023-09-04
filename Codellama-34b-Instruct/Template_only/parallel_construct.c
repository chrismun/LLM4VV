#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with 4 threads
    #pragma acc parallel num_threads(4)
    {
        // Create a loop with 10 iterations
        for (int i = 0; i < 10; i++) {
            // Create a data region with 4 elements
            #pragma acc data copy(i)
            {
                // Create a loop with 4 iterations
                for (int j = 0; j < 4; j++) {
                    // Perform some computation
                    i += j;
                }
            }
        }
    }

    // Check that the data region was executed correctly
    if (i != 10) {
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