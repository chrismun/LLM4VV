#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable that will be used to store the result of the link clause
    int result;

    // Declare a compute construct that will be used to execute the link clause
    #pragma acc parallel
    {
        // Declare a variable that will be used to store the result of the link clause
        int result;

        // Declare a link clause that will be used to link the variable to the compute construct
        #pragma acc link(result)

        // Execute the link clause
        result = 1;
    }

    // Check that the result of the link clause is correct
    if (result != 1) {
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