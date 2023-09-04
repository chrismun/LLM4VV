#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a variable to be used in the OpenACC region
    int x = 0;

    // Declare a parallel region
    #pragma acc parallel
    {
        // Declare a variable to be used in the parallel region
        int y = 0;

        // Declare a loop to be executed in parallel
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // Do some work
            y += i;
        }
    }

    // Check that the variable x is not modified in the parallel region
    if (x != 0) {
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