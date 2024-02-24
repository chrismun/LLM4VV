#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable to be used in the OpenACC region
    int var;

    // Open an OpenACC region
    #pragma acc parallel copy(var)
    {
        // Check that the variable is accessible in the OpenACC region
        if (&var == NULL) {
            err++;
        }
    }

    // Check that the variable is still accessible outside the OpenACC region
    if (&var == NULL) {
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