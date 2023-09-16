#include <stdio.h>
#include <stdlib.h>
#include "openacc.h"
#include "acc_testsuite.h"

#ifndef T1
//T1:acc set device num, V:2.7-3.3
int test1() {
    int err = 0;
    int numDevices = acc_get_num_devices(acc_device_default);
    if(numDevices > 0){
       for(int dev_num=0; dev_num<numDevices; ++dev_num) {
            acc_set_device_num(dev_num, acc_device_default);
            if(acc_get_device_num(acc_device_default) != dev_num) {
                err = 1;
                break;
            }
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}