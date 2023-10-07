#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Add code to test shutdown directive here
    // ...

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

In place of "// Add code to test shutdown directive here", add code to test the shutdown directive.

The shutdown directive shuts down the connection to the given device or devices of the given device type, and frees any associated runtime resources. This ends all data lifetimes in device memory.

To correctly test the shutdown directive, you can use OpenACC runtime APIs to query the available devices, select a device to shutdown, and call the shutdown directive with the selected device type and device number.

Here is an example code snippet to test the shutdown directive for all available devices:

#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Query the number of devices
    int numDevices = acc_get_num_devices(acc_device_nvidia);

    // Iterate over all available devices
    for (int i = 0; i < numDevices; i++) {
        // Get the device type and number
        acc_device_t devType;
        int devNum;
        acc_get_device_type(&devType, &devNum, i);

        // Check if the device type is NVIDIA
        if (devType == acc_device_nvidia) {
            // Shutdown the device
            #pragma acc shutdown device_type(acc_device_nvidia) device_num(i)
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}