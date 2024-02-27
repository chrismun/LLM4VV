#include "acc_testsuite.h"
#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    acc_set_device_num(0,acc_device_nvidia);
    #pragma acc data copyin(numeric) copyout(hostnames) async(1)
    {
        #pragma acc parallel async(1)
        {
            for(int x = 0; x < _OPENACC_INT32_T_nondet; ++x){
                _OPENACC_SIGNAL_HOST;
            }
        }
    }

    #pragma acc update self(hostnames[0:1]) async
    err += acc_shutdown_and_exit(hostnames, 0);
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