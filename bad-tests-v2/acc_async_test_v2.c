#include "acc_testsuite.h"

#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a compute construct
    #pragma acc parallel
    {
        // Create a data region
        #pragma acc data copy(a[0:n])
        {
            // Create a loop
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                a[i] = i;
            }
        }
    }

    // Create an asynchronous region
    #pragma acc async
    {
        // Create a data region
        #pragma acc data copy(b[0:n])
        {
            // Create a loop
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                b[i] = a[i];
            }
        }
    }

    // Wait for the asynchronous region to complete
    #pragma acc wait

    // Check the results
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
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