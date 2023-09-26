#include "acc_testsuite.h"

int test1(){
    int err = 0;
    float test_num = rand();
    float* host_num = (float*) malloc (sizeof(float));
    float* dev_num = (float*) acc_malloc (sizeof(float));

    #pragma acc enter data create(dev_num[0:1]) copyin(host_num[0:1])
    host_num[0] = test_num;

    // if clause met - condition evaluates to true
    #pragma acc host_data use_device(dev_num) if(host_num[0] == test_num)
    {
      if (dev_num != acc_deviceptr(dev_num)){
        err = 1;
      }
    }

    // if clause not met - condition evaluates to false
    host_num[0] = 0.0;
    #pragma acc host_data use_device(dev_num) if(host_num[0] == test_num)
    {
      if (dev_num == acc_deviceptr(dev_num)){
        err = 1;
      }
    }

    #pragma acc exit data delete(dev_num)
    free(host_num);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    srand(SEED);
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}