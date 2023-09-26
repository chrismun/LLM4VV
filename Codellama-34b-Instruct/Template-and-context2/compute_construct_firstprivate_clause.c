#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a shared variable
    int shared_var = 0;

    // create a private variable
    int private_var = 0;

    // create a firstprivate variable
    int firstprivate_var = 0;

    // create a compute construct with firstprivate clause
    #pragma acc compute firstprivate(firstprivate_var)
    {
        // increment the shared variable
        shared_var++;

        // increment the private variable
        private_var++;

        // increment the firstprivate variable
        firstprivate_var++;
    }

    // check that the firstprivate variable was not modified
    if (firstprivate_var != 0) {
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