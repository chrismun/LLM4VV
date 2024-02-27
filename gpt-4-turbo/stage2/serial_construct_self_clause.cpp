#include <iostream>
#include <openacc.h>
#include <stdlib.h>

// Define acc_testsuite.h functionality as required, assuming basics are set
#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int host_var = rand(); // Original value for the variable
    int original_host_var = host_var; // Store the original value for comparison
    
    #pragma acc serial copyin(host_var) self(host_var)
    {
        // Attempt to modify host_var. Due to the 'self' clause,
        // changes here should not affect the original variable outside this region.
        host_var = rand();
    }
    
    // Verify the variable was not changed by the serial region due to the 'self' clause
    if (host_var != original_host_var) {
        err++;
        std::cerr << "Serial construct self clause failed to isolate changes to the host_var." << std::endl;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}