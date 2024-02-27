#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int memory_prop = acc_get_property(1, acc_device_none, acc_property_memory);
    char *name_prop =  acc_get_property_string(0, acc_device_none, acc_property_name);

    if(memory_prop == 0 || name_prop == NULL){
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