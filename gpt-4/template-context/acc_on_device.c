#include "openacc.h"
#include "acc_testsuite.h"

#define NUM_TEST_CALLS 100
#define SEED 12345

#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        if(!acc_on_device(acc_device_not_host)){
            err = 1;
        }
    }

    #pragma acc parallel device_type(acc_device_host)
    {
        if(acc_on_device(acc_device_not_host)){
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
        failed += test1();
    }
    if(failed != 0){
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}