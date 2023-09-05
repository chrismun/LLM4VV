#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Perform computation using the OpenACC loop construct with private clause
    #pragma acc parallel loop private(err)
    for (int i = 0; i < 100; i++){
        int privateVar = 0;

        // Modify the private variable within the loop body
        privateVar = privateVar + i;

        // Check if the private variable is correctly updated
        if (privateVar != i){
            err = 1;
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