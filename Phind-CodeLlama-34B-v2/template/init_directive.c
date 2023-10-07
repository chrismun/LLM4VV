#include "acc_testsuite.h"
#ifndef T1
//T1:init directive,V:2.7-3.3
int test1(){
    int err = 0;

    #pragma acc init device_type(host)
    {
        #pragma acc loop reduction(+:err)
        for (int x = 0; x < 100; ++x){
            err += x;
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