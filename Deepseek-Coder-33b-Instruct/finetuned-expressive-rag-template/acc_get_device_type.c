#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:acc get device type,V:2.7-3.3
int test1(){
    int err = 0;

    acc_device_t device_type = acc_get_device_type();

    if (device_type == acc_device_none) {
        printf("Device type is acc_device_none\n");
        err = 1;
    } else {
        printf("Device type is not acc_device_none\n");
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}