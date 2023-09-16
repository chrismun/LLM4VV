#include "acc_testsuite.h"

//T1:acc is present,V:2.7-3.3
int test1() {
    int err = 0;
    int deviceCount = 0;
    #pragma acc parallel copy(deviceCount)
    {
        deviceCount = acc_get_num_devices(acc_device_all);
    }

    if(deviceCount == 0){
        err = 1;
    }
    
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}