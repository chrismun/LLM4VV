#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc declare device_resident(a_device)
    int a_device[10];

    #pragma acc parallel
    {
        #pragma acc loop
            for (int x = 0; x < 10; ++x){
                a_device[x] = -1;
            }
    }

    #pragma acc kernels
    #pragma acc loop
    for (int x = 0; x < 10; ++x){
        if (a_device[x] != -1){
            err += 1;
        }
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