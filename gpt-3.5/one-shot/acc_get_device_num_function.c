#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    int device_num = 0;
    #pragma acc parallel present(device_num)
    {
        #pragma acc data present(device_num)
        {
            // Get the device number where the code is being executed
            device_num = acc_get_device_num();
        }
    }

    if (device_num < 0){
        err += 1;
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