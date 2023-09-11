#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Get the device number and type
    int dev_num = rand() % 10;
    acc_device_t dev_type = acc_device_current;

    // Get the property value
    size_t property_value = acc_get_property(dev_num, dev_type, acc_property_memory);

    // Check if the property value is valid
    if (property_value == 0) {
        std::cerr << "Error: acc_get_property returned 0 for device " << dev_num << " and type " << dev_type << std::endl;
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