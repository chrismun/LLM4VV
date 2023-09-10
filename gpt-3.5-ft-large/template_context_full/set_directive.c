#include "acc_testsuite.h"
#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(DEFAULT_DEVICE_TYPE == acc_get_device_type()){
        #pragma acc set device_type(host)
        if(acc_get_device_type() != host_type){
            err += 1;
            //resets to default device type
            #pragma acc set device_type()
        }
        #pragma acc set device_type(DEFAULT_DEVICE_TYPE)
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