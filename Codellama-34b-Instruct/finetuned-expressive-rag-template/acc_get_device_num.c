#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = rand() % acc_get_num_devices(acc_device_default);
    acc_set_device_num(device_type, acc_device_default);

    int device_num = acc_get_device_num(acc_device_default);

    if (device_num != device_type){
        err = 1;
        printf("acc_get_device_num returned %d, but expected %d\n", device_num, device_type);
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