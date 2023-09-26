#include "acc_testsuite.h"

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region with a single variable
    int a = 0;
    #pragma acc data attach(a)
    {
        // Attach the variable to the data region
        #pragma acc attach(a)

        // Perform some operations on the variable
        a = 1;
        a = a + 1;

        // Detach the variable from the data region
        #pragma acc detach(a)
    }

    // Check that the variable has been updated correctly
    if (a != 2) {
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