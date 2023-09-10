#include "acc_testsuite.h"

#ifndef T1
//T1:attachment counter,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = acc_get_device_type();
    if (device_type == acc_device_host) {
        // Host device, no attachment counter
        return 0;
    }

    int num_devices = acc_get_num_devices(device_type);
    for (int i = 0; i < num_devices; i++) {
        int device_id = acc_get_device_id(device_type, i);
        int attachment_counter = acc_get_attachment_counter(device_id);
        if (attachment_counter != 0) {
            // Attachment counter is not zero, test failed
            err = 1;
            break;
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