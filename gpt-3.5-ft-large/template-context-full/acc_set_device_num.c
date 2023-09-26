#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    //This code was written to be an example. It may not function in high performance computing.
    int device_num = -1;
    acc_set_device_num(device_num, acc_device_nvidia);

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