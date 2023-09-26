#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4; // Set the number of workers to 4
    int num_threads = 8; // Set the number of threads to 8

    // Create a parallel region with the specified number of workers
    #pragma acc parallel num_workers(num_workers)
    {
        // Create a loop with the specified number of iterations
        #pragma acc loop
        for (int i = 0; i < num_threads; i++) {
            // Do some work
        }
    }

    // Check that the number of workers is correct
    if (num_workers != acc_get_num_workers()) {
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