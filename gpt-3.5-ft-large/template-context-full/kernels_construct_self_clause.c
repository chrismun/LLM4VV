#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() == acc_device_none){
        return 0;
    }
    #pragma acc data copy(err)
    {
        #pragma acc kernels self
        {
            if (acc_get_device_type() != acc_device_none){
                err = 1;
            }
        }
        #pragma acc kernels loop reduction(+:err)
        for (int x = 0; x < 1; ++x){
            if (acc_get_device_type() == acc_device_host){
                err = err;
            }
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