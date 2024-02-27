#include "acc_testsuite.h"
#ifndef T1
//T1:acc get device type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t device_type = acc_get_device_type();
    if (device_type != acc_device_none) {
        // Device type has been defined
        err += 0;
    }
    else {
        // Device type has not been defined
        err += 1;
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