#include "acc_testsuite.h"
#ifndef T1
//T1:update directive,V:2.7-3.3
int test1(){
    int err = 0;
    int length = 100;
    int data_host[length];
    int data_device[length];
    
    // Fill data_host with some values
    for (int idx = 0; idx < length; ++idx) {
        data_host[idx] = idx;
    }
    
    srand(SEED);
    #pragma acc parallel copy(data_device)
    {
        for(int idx = 0; idx < length; ++idx){
            data_device[idx] = data_host[idx];
        }
    }
    #pragma acc update host(data_device)
    for(int idx = 0; idx < length; ++idx){
      if(data_host[idx] != data_device[idx]){
        err = 1;
        break;
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