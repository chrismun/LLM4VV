#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int memory = acc_get_property(1, acc_device_nvidia, acc_property_memory);
    int free_memory = acc_get_property(1, acc_device_nvidia, acc_property_free_memory);
    int shared_memory_support = acc_get_property(1, acc_device_nvidia, acc_property_shared_memory_support);
    int image_support = acc_get_property(1, acc_device_nvidia, acc_property_image);
    size_t bytes;
    #pragma acc compute device_type(acc_device_nvidia) async(1) 
    {
      #pragma acc host_data use_device(data)
      {
        bytes = acc_deviceptr_property(data, prop_allocate);
      }
    }
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