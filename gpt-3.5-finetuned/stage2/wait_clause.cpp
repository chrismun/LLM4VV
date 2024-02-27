#include "acc_testsuite.h"
#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_set_device_num(1,acc_device_nvidia);
    #pragma acc data copyin(n,v) create(nv) device(1)
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            v[x] = sin(nv[x]));
        }
        #pragma acc update host(v) async(1)
        acc_set_device_num(0,acc_device_nvidia);
        #pragma acc exit data copyin(v) async(1) wait(1)
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