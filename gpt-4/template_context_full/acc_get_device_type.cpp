#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:acc get device type,V:2.0-2.7*/
int test1(){
    int err = 0;
    acc_device_t device_type;

    device_type = acc_get_device_type();

    // Check if the device type has been correctly identified
    if(device_type == acc_device_none){
        // If the device type is not defined
        printf("Device type not defined\n");
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