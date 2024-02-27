#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Assuming acc_testsuite.h defines these or they are provided as constants
#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Global variable declared as device resident
#pragma acc declare create(dev_var)
int dev_var = 5;

// Test Function
int test1(){
    int err = 0;
    int host_var = 0;

    // Trying to access device_resident variable in parallel region
    #pragma acc parallel copyout(host_var)
    {
        host_var = dev_var;
    }

    // Check if the device_resident variable was accessible
    if (host_var != dev_var) {
        // In a real device scenario, this might indicate an issue with the device resident memory allocation
        // For simplicity here, differ from the expected value indicates a problem (though it's more complex in practice)
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;

#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}