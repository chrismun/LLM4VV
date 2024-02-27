#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_init(acc_device_default);

    #pragma acc data copyout(err)
    {
        #pragma acc compute num_workers(16) reduction(+:err)
        for (int y = 0; y < 10; ++y){
            #pragma acc loop worker
            for (int x = 0; x < 1000; ++x){
                if (acc_get_worker_num(acc_get_device_type()) > 15){
                    err += 1;
                }
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