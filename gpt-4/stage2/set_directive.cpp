#include "acc_testsuite.h"
#ifndef T1
/*T1:set directive,V:2.0-2.7*/
int test1(){
    int err = 0;

    // OpenACC can support up to acc_device_last device types.
    for (int device_type = acc_device_none; device_type < acc_device_last; ++device_type){
        if (acc_get_num_devices(device_type) > 0) {
            // Set the device number to 0 for the current device type.
            #pragma acc set device_num(0) device_type(device_type)
            // Check if the set operation was successful.
            if (acc_get_device_type() != device_type || acc_get_device_num(device_type) != 0) {
                err = 1;
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