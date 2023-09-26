#include <iostream>
#include <cstdlib>
#include <cstring>
#include "openacc.h"

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
/*T1:acc get property,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int dev_num = 0;
    acc_device_t dev_type = acc_get_device_type(dev_num);
    acc_device_property_t property = acc_property_memory;

    size_t memory_size = acc_get_property(dev_num, dev_type, property);

    if (memory_size == 0){
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