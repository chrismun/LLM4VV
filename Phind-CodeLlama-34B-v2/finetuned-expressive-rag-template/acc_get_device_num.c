#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = acc_get_device_type();
    if (device_type == acc_device_default) {
        device_type = acc_device_host;
    }

    int device_num = acc_get_device_num(device_type);
    if (device_num == -1) {
        printf("acc_get_device_num failed: No devices of type %d found.\n", device_type);
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