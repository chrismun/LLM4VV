#include "acc_testsuite.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#ifndef T2
//T2:declare,link,V:1.0-2.7

real_t linked_var = 123.456; // A variable to be linked

int test2(){
    int err = 0;
    real_t host_val = 0;

    // Modify linked_var in a parallel region
    #pragma acc parallel
    {
        #pragma acc declare link(linked_var)
        linked_var += 10;
    }

    // Copy back to a host value to check
    host_val = linked_var;

    // Check the value has been updated correctly
    if(fabs(host_val - 133.456) > PRECISION){
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1); // Updating to use bit 1 for test 2 failure indication
    }
#endif
    printf("Test %s\n", failcode ? "FAILED" : "PASSED");
    return failcode;
}