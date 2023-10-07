#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host_data construct with an if_present clause
    #pragma acc host_data if_present(var)
    {
        // Do something with var
        var = 1;
    }

    // Check if var is present in the current device memory
    if (var != 1) {
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