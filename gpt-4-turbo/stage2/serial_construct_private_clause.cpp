#include <iostream>
#include <stdlib.h>
#include <openacc.h>

// Assuming acc_testsuite.h defines constants like SEED and NUM_TEST_CALLS, or define them here
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:serial construct private clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int original_value = rand() % 100; // Random number as original value
    int var = original_value;
    
    #pragma acc serial private(var)
    {
        // Within the serial region, modify var
        var = 999;
    }
    
    // If var was truly private within the serial construct, its value outside should remain unchanged
    if (var != original_value) {
        err++;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}