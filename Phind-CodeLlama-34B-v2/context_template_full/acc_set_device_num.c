#include "acc_testsuite.h"
#ifndef T1
/*T1:acc set device num,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int dev_num = rand() % 10; // Random device number
    acc_device_t dev_type = acc_device_default; // Default device type

    acc_set_device_num(dev_num, dev_type);

    if (acc_get_device_num() != dev_num){
        err = 1;
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