#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a serial construct with an async clause
    #pragma acc serial async
    {
        // Do some work
        int i = 0;
        while (i < 100) {
            i++;
        }
    }

    // Check that the async clause was executed correctly
    if (i != 100) {
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