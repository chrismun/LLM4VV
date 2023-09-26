#include "acc_testsuite.h"

#ifndef T1
//T1:routine directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a routine that takes no arguments and returns an integer
    int (*routine)() = acc_routine_create(NULL, NULL, NULL, 0);

    // Call the routine and check the result
    int result = routine();
    if (result != 0) {
        err = 1;
    }

    // Destroy the routine
    acc_routine_destroy(routine);

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