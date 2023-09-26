#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct self clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a parallel region with a self clause
    #pragma acc parallel self(true)
    {
        // do some work
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // do some work
        }
    }

    // create a serial region with a self clause
    #pragma acc serial self(true)
    {
        // do some work
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // do some work
        }
    }

    // create a kernels region with a self clause
    #pragma acc kernels self(true)
    {
        // do some work
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // do some work
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