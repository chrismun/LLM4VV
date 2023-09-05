#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device
    acc_device_t device = acc_get_device(acc_device_default);

    // Create a new context
    acc_context_t context = acc_create_context(device, NULL);

    // Attach the context to the device
    acc_attach_context(context, device);

    // Create a new data region
    acc_data_region_t data_region = acc_create_data_region(context, NULL);

    // Attach the data region to the device
    acc_attach_data_region(data_region, device);

    // Create a new executable data region
    acc_executable_data_region_t executable_data_region = acc_create_executable_data_region(context, NULL);

    // Attach the executable data region to the device
    acc_attach_executable_data_region(executable_data_region, device);

    // Create a new construct
    acc_construct_t construct = acc_create_construct(context, NULL);

    // Attach the construct to the device
    acc_attach_construct(construct, device);

    // Create a new executable construct
    acc_executable_construct_t executable_construct = acc_create_executable_construct(context, NULL);

    // Attach the executable construct to the device
    acc_attach_executable_construct(executable_construct, device);

    // Create a new data region
    acc_data_region_t data_region2 = acc_create_data_region(context, NULL);

    // Attach the data region to the device
    acc_attach_data_region(data_region2, device);

    // Create a new executable data region
    acc_executable_data_region_t executable_data_region2 = acc_create_executable_data_region(context, NULL);

    // Attach the executable data region to the device
    acc_attach_executable_data_region(executable_data_region2, device);

    // Create a new construct
    acc_construct_t construct2 = acc_create_construct(context, NULL);

    // Attach the construct to the device
    acc_attach_construct(construct2, device);

    // Create a new executable construct
    acc_executable_construct_t executable_construct2 = acc_create_executable_construct(context, NULL);

    // Attach the executable construct to the device
    acc_attach_executable_construct(executable_construct2, device);

    // Detach the data region from the device
    acc_detach_data_region(data_region, device);

    // Detach the executable data region from the device
    acc_detach_executable_data_region(executable_data_region, device);

    // Detach the construct from the device
    acc_detach_construct(construct, device);

    // Detach the executable construct from the device
    acc_detach_executable_construct(executable_construct, device);

    // Detach the data region from the device
    acc_detach_data_region(data_region2, device);

    // Detach the executable data region from the device
    acc_detach_executable_data_region(executable_data_region2, device);

    // Detach the construct from the device
    acc_detach_construct(construct2, device);

    // Detach the executable construct from the device
    acc_detach_executable_construct(executable_construct2, device);

    // Destroy the context
    acc_destroy_context(context);

    // Destroy the device
    acc_destroy_device(device);

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