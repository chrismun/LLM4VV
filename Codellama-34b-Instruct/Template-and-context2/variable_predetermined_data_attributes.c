#include "acc_testsuite.h"

#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;

    // declare a variable that is private to each thread
    int thread_private_var = 0;

    // declare a variable that is private to the worker
    int worker_private_var = 0;

    // declare a variable that is private to the gang
    int gang_private_var = 0;

    // declare a variable that is shared across all threads
    int shared_var = 0;

    // create a compute construct with a loop directive
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        // increment the private variables
        thread_private_var++;
        worker_private_var++;
        gang_private_var++;

        // increment the shared variable
        shared_var++;
    }

    // check that the private variables have the correct values
    if (thread_private_var != 10) {
        err++;
    }
    if (worker_private_var != 10) {
        err++;
    }
    if (gang_private_var != 10) {
        err++;
    }

    // check that the shared variable has the correct value
    if (shared_var != 100) {
        err++;
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