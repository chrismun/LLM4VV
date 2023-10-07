#include "acc_testsuite.h"

//T1:reference counters,V:2.7-3.3
int test1(){
    int i;
    int err = 0;
    int num_dev = acc_get_num_devices( acc_device_default );
    int* dev_refcount = (int*)malloc( sizeof(int)*num_dev );

    #pragma acc enter data copyin(dev_refcount[0:num_dev])
    for(i=0; i<num_dev; i++) { 
        dev_refcount[i] = acc_get_device_num( acc_device_default );
        if(dev_refcount[i] != 1)
            err = 1;
    }    
    #pragma acc exit data delete(dev_refcount[0:num_dev])
  
    free(dev_refcount);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}