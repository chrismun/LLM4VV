#include "acc_testsuite.h"

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with a compute construct
    #pragma acc parallel
    {
        // Create a serial region with a compute construct
        #pragma acc serial
        {
            // Create a kernels region with a compute construct
            #pragma acc kernels
            {
                // Do some work
                int i = 0;
                #pragma acc loop
                for (i = 0; i < 10; i++) {
                    #pragma acc atomic
                    {
                        // Do some work
                    }
                }
            }
        }
    }

    // Check if the work was done correctly
    if (err != 0) {
        return 1;
    }

    return 0;
}
#endif

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if (failed != 0){
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}