#include "acc_testsuite.h"

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default async value to 1
    acc_set_default_async(1);

    // Create a compute construct
    #pragma acc parallel
    {
        // Do some work
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 10; i++) {
            // Do some work
        }
    }

    // Check if the async value is set to 1
    if (acc_get_async() != 1) {
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