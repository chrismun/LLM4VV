#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop
    for (int i = 0; i < 1000000; ++i) {
        // Perform some calculations
        // ...

        #pragma acc serial
        {
            // Code that needs to be executed serially
            // ...
        }
        
        // Continue with other parallel computations
        // ...
    }

    if () {
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}