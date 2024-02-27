#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int test_val = 0;
    int condition = 1; // This will control the conditional execution

    // Test with condition true
    #pragma acc serial if(condition)
    {
        test_val = 1; // This should execute because condition is true
    }
    if(test_val != 1){ // Check if the serial construct executed
        err += 1;
    }

    test_val = 0; // Reset test value
    condition = 0; // Change condition to false

    // Test with condition false
    #pragma acc serial if(condition)
    {
        test_val = 1; // This should not execute because condition is false
    }
    if(test_val != 0){ // Check if the serial construct did not execute
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