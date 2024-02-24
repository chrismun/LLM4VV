#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc init,V:2.7-3.3
int test1(){
    int err = 0;

    // Initialize a device
    acc_init(acc_device_default);

    // Check if the device was successfully initialized
    if (acc_get_device_type() == acc_device_default) {
        printf("Device successfully initialized\n");
    } else {
        printf("Device initialization failed\n");
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
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}