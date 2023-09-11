#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:acc set device type,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t device_type = (acc_device_t)(rand() % acc_get_num_devices(acc_device_default));
    acc_set_device_type(device_type);

    if (acc_get_device_type() != device_type){
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