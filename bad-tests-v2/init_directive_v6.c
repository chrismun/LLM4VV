#include "acc_testsuite.h"
#include <stdlib.h>

//T1:init directive,V:2.7-3.3
int test1(){
    int err = 0;

    #pragma acc init device_type(device_type1)
    if(!acc_is_init(acc_device_type1)){
        err = 1;
    }
    
    #pragma acc init device_type(device_type2)
    if(!acc_is_init(acc_device_type2)){
        err = 1;
    }
    
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}