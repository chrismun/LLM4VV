#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new OpenACC context
    acc_context_t context = acc_create_context();

    // Set the OpenACC device to the current device
    acc_set_device(context, acc_get_device());

    // Get the OpenACC device properties
    acc_device_properties_t properties;
    acc_get_device_properties(context, &properties);

    // Check if the device supports the OpenACC runtime
    if (!properties.runtime_support) {
        err = 1;
    }

    // Check if the device supports the OpenACC data construct
    if (!properties.data_support) {
        err = 1;
    }

    // Check if the device supports the OpenACC executable-data construct
    if (!properties.executable_data_support) {
        err = 1;
    }

    // Check if the device supports the OpenACC construct-independent construct
    if (!properties.construct_independent_support) {
        err = 1;
    }

    // Check if the device supports the OpenACC V:2.0-2.7 version
    if (!properties.version_support) {
        err = 1;
    }

    // Destroy the OpenACC context
    acc_destroy_context(context);

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