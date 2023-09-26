#include "acc_testsuite.h"

#ifndef T1
/*T1:acc set default async,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);
    int test_val = rand();

    acc_set_default_async(1);
    
    #pragma acc parallel async
    {
        test_val = 2 * test_val;
    }
    
    acc_wait(1);

    // This assumes that if the test_val is not double, the set default async did not work properly
    if (test_val != 2 * SEED) {
        err = 1;
    }

    return err;
}
#endif

int main() {
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