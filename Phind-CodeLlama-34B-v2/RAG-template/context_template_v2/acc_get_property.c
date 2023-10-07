#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    int dev_num = 0;
    acc_device_t dev_type = acc_device_current;
    acc_device_property_t property = acc_property_memory;
    size_t result = acc_get_property(dev_num, dev_type, property);

    if (result == 0) {
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