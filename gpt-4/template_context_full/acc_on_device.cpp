#include "acc_testsuite.h"
#ifndef T1
/*T1:acc on device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    // Test if code is running on host
    if(!acc_on_device(acc_device_host)){
        printf("Test failed: code is not running on host\n");
        err = 1;
    }

    // Test if code is running on non-host device
    #pragma acc parallel
    {
        if(!acc_on_device(acc_device_not_host)){
            printf("Test failed: code is not running on non-host device\n");
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
    if(failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}