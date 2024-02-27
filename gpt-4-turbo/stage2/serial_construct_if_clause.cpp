#include <cstdlib>
#include <iostream>

// Mock header for the test setup - replace this with actual OpenACC testing infrastructure
#include "acc_testsuite.h"

#ifndef T1
// T1:serial construct if clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int a = 0;
    int condition_true = 1;
    int condition_false = 0;

    #pragma acc serial if(condition_true)
    {
        a += 1; // Should execute because condition is true
    }

    #pragma acc serial if(condition_false)
    {
        a += 1; // Should not execute because condition is false
    }

    // If the accelerator if clause is working, `a` should be 1
    if (a != 1) {
        err += 1;
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