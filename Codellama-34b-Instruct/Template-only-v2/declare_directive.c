#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable
    int x = 0;

    // Use the declare directive to declare a variable
    #pragma acc declare create(x)

    // Use the variable in a compute construct
    #pragma acc parallel
    {
        x = 1;
    }

    // Check that the variable was declared correctly
    if (x != 1) {
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