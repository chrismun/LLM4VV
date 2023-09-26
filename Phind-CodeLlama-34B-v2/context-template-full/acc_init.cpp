#include "acc_testsuite.h"
#ifndef T1
/*T1:acc init,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t dev_type = (acc_device_t)(rand() % acc_get_num_devices(acc_device_host));
    int dev_num = rand() % acc_get_num_devices(dev_type);

    acc_init_device(dev_num, dev_type);

    if (acc_get_device_type() != dev_type || acc_get_device_num(dev_type) != dev_num){
        err = 1;
    }

    acc_shutdown(dev_type);

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