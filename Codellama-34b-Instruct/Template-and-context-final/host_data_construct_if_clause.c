#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host_data construct with an if clause
    #pragma acc host_data if(condition)
    {
        // Do something within the host_data construct
        int x = 0;
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            x += i;
        }

        // Check that the if clause is working correctly
        if (x != 45) {
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