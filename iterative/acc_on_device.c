#include "acc_testsuite.h"

#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Check if acc_on_device returns true inside a compute region
    #pragma acc parallel
    {
        if (!acc_on_device(acc_device_not_host)) {
            err = 1;
        }
    }

    // Check if acc_on_device returns false outside a compute region
    if (acc_on_device(acc_device_not_host)) {
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