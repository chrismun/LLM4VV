#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    int array[100];

    for (int i = 0; i < 100; i++)
        array[i] = i;

    #pragma acc loop device_type(nvidia) 
    for (int i = 0; i < 100; i++){
        array[i] += i;
    }

    // verify correctness 
    for (int i = 0; i < 100; i++)
        if (array[i] != (2 * i))
            err = 1;

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