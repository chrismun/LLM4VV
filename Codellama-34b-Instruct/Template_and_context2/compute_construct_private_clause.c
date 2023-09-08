#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct private clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create a parallel region with a private clause
    #pragma acc parallel private(x)
    {
        // create a serial region with a private clause
        #pragma acc serial private(y)
        {
            // create a kernels region with a private clause
            #pragma acc kernels private(z)
            {
                // do some work
            }
        }
    }

    // check that the private variables were created correctly
    if (x != 0 || y != 0 || z != 0) {
        err = 1;
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