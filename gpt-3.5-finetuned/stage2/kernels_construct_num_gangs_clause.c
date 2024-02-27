#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,construct,num_gangs,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        printf("On device\n");
    int temp = 1;
    int *dev_test;
    dev_test = (int *)malloc(10 * sizeof(int));
    for (int x = 0; x < 10; ++x){
        dev_test[x] = 0;
    }
    #pragma acc enter data copyin(dev_test[0:10])
    #pragma acc kernels num_gangs(2000)
    {
        #pragma acc loop
        for (int x = 0; x < 2000; ++x){
            dev_test[(int) (10.0 * rand() / (RAND_MAX + 1.0))]++;
        }
    }
    #pragma acc exit data copyout(dev_test[0:10])
    for (int x = 0; x < 10; ++x){
        if (dev_test[x] < (2000 / 10 - 500) || dev_test[x] > (2000 / 10 + 500)){
            err += 1;
            break;
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