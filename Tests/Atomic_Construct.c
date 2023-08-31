#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the shared variable
    int shared_var = 0;

    // Create a parallel region
    #pragma acc parallel
    {
        // Declare the atomic variable
        int atomic_var;

        // Initialize the atomic variable
        atomic_var = 0;

        // Increment the shared variable in parallel
        #pragma acc atomic
        shared_var++;

        // Increment the atomic variable in parallel
        #pragma acc atomic
        atomic_var++;

        // Check if the shared variable and the atomic variable are equal
        if (shared_var != atomic_var){
            err = 1;
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