#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a gang of threads
    #pragma acc gang
    {
        // Create a loop construct
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // Do some work
            #pragma acc parallel
            {
                // Do some work
            }
        }
    }

    // Check that the gang is working correctly
    if (acc_get_num_gangs() != 1) {
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