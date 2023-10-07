#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int length = 100;
    int host_arr[length];
    int dev_arr[length];
    int x;
    
    #pragma acc enter data create(dev_arr[:length])
    for(x = 0; x < length; x++){
        host_arr[x] = rand();
    }
    
    #pragma acc host_data use_device(dev_arr)
    {
        for(x = 0; x < length; x++){
            dev_arr[x] = host_arr[x];
        }
    }
    
    #pragma acc update host(dev_arr[:length])

    for(x = 0; x < length; x++){
        if(dev_arr[x] != host_arr[x]){
            err = 1;
        }
    }

    #pragma acc exit data delete(dev_arr)

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