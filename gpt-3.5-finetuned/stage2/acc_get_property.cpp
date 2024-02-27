#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int dev_type = acc_get_device_type();       // get device type in use
    int spirit_spec;

    spirit_spec = acc_get_property(1, static_cast<acc_device_t>(dev_type), acc_property_shared_memory_support);
    if (spirit_spec == 0){
          spirit_spec = 1;
    }

    return 0;
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