#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int device_num = acc_get_device_num(ACC_DEVICE_TYPE_GPU);
    if (device_num == -1) {
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