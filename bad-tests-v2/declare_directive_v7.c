#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;

    // declare a variable in device memory
    int a;
    #pragma acc declare create(a)

    // copy the value of a from host to device
    #pragma acc update device(a)

    // perform some computation on the device
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        a += i;
    }

    // copy the value of a from device to host
    #pragma acc update host(a)

    // check the result
    if (a != 45) {
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