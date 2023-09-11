#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a private variable for each gang in all dimensions
    int private_var = 0;

    // Use the private variable in a serial construct
    #pragma acc serial private(private_var)
    {
        // Do some work with the private variable
        private_var++;
    }

    // Check that the private variable was updated correctly
    if (private_var != 1) {
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