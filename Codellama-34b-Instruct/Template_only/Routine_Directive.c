#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a routine that takes a single argument
    acc routine(void) {
        // Do something with the argument
        int arg = 0;
        // ...
        return arg;
    }

    // Call the routine with a random argument
    int arg = rand();
    int result = routine(arg);

    // Check that the result is correct
    if (result != arg) {
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