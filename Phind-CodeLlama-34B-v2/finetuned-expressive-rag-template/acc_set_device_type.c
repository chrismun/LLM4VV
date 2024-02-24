#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t device_type = acc_get_device_type();
    acc_set_device_type(device_type == acc_device_host ? acc_device_not_host : acc_device_host);

    if (acc_get_device_type() == device_type) {
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