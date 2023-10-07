#include "acc_testsuite.h"
#ifndef T1
//T1:acc init,V:2.7-3.3
int test1(){
    int err = 0;
    int dev_type = acc_device_default;
    int dev_num = 0;

    acc_init(dev_type);
    acc_init_device(dev_num, dev_type);

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