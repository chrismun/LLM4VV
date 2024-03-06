#include "acc_testsuite.h"

#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t default_device_type = acc_device_default;
    acc_set_device_type(default_device_type);

    if (acc_get_device_type() != default_device_type) {
        err++;
    }

    acc_device_t host_device_type = acc_device_host;
    acc_set_device_type(host_device_type);

    if (acc_get_device_type() != host_device_type) {
        err++;
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