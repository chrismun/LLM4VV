#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#define acc_property_memory 1
#define acc_property_free_memory 2
#define acc_property_shared_memory_support 3
#define acc_property_name 4
#define acc_property_vendor 5
#define acc_property_driver 6

int test1(){
    int err = 0;
    srand(SEED);

    int dev_num = acc_get_device_num(acc_device_current);
    acc_device_t dev_type = acc_get_device_type();

    size_t memory = acc_get_property(dev_num, dev_type, acc_property_memory);
    size_t free_memory = acc_get_property(dev_num, dev_type, acc_property_free_memory);
    int shared_memory_support = acc_get_property(dev_num, dev_type, acc_property_shared_memory_support);
    const char* name = acc_get_property_string(dev_num, dev_type, acc_property_name);
    const char* vendor = acc_get_property_string(dev_num, dev_type, acc_property_vendor);
    const char* driver = acc_get_property_string(dev_num, dev_type, acc_property_driver);

    if (memory == 0 || free_memory == 0 || shared_memory_support == 0 || name == NULL || vendor == NULL || driver == NULL) {
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}