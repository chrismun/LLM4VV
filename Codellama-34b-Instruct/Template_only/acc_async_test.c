#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new asynchronous region
    #pragma acc async
    {
        // Perform some computation in the asynchronous region
        #pragma acc parallel loop
        for (int i = 0; i < 100; i++) {
            int a = i * 2;
            int b = i * 3;
            int c = a + b;
            if (c != i * 5) {
                err = 1;
                break;
            }
        }
    }

    // Wait for the asynchronous region to complete
    #pragma acc wait

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