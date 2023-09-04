#include "acc_testsuite.h"

//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a compute region
    #pragma acc parallel
    {
        // Call a procedure
        int result = procedure_call();

        // Check the result
        if (result != 0) {
            err = 1;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}