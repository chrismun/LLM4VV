#include "acc_testsuite.h"
#include <stdio.h>
#ifndef T1
//T1:serial construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int testValue = 42;
    int testData = 0;

    #pragma acc serial vector_length(32)
    {
        testData = testValue;
    }

    // Verify operation within the serial construct was performed
    if (testData != testValue) {
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
        if (test1() != 0) {
            failed++;
        }
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    
    // Report test status and return failcode
    if (failcode == 0) {
        printf("PASS: OpenACC serial construct vector_length clause is supported and functioning.\n");
    } else {
        printf("FAIL: Issues detected with OpenACC serial construct vector_length clause.\n");
    }

    return failcode;
}