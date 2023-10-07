#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a global variable that will be used in an accelerator routine
    int global_var = 0;

    // Declare a link clause for the global variable
    #pragma acc declare link(global_var)

    // Use the global variable in an accelerator routine
    #pragma acc parallel
    {
        global_var = 1;
    }

    // Check that the global variable has been updated
    if (global_var != 1) {
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