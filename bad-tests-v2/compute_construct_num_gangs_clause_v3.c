#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_threads = num_gangs * num_workers;

    // Create a parallel region with the specified number of gangs and workers
    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
    {
        // Create a loop with the specified number of iterations
        #pragma acc loop
        for (int i = 0; i < num_threads; i++) {
            // Do some work
            #pragma acc loop
            for (int j = 0; j < 10; j++) {
                // Do some more work
            }
        }
    }

    // Check that the number of threads created matches the expected number
    if (num_threads != acc_get_num_threads()) {
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