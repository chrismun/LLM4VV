#include "acc_testsuite.h"

// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_gangs = 10;
    int num_workers = 10;
    int num_threads = 10;

    // Create a parallel region with num_gangs gangs
    #pragma acc parallel num_gangs(num_gangs)
    {
        // Create a loop with num_workers workers
        #pragma acc loop worker(num_workers)
        for (int i = 0; i < num_threads; i++) {
            // Do some work
        }
    }

    // Check that the number of gangs is correct
    if (acc_get_num_gangs() != num_gangs) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}