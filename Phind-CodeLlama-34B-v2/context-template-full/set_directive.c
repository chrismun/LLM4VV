#include "acc_testsuite.h"
#ifndef T1
/*T1:set directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int device_num = rand() % 10;
    int device_type = rand() % 2;
    int default_async = rand() % 3;

    #pragma acc set device_num(device_num)
    #pragma acc set device_type(device_type)
    #pragma acc set default_async(default_async)

    if (acc_get_device_num() != device_num || acc_get_device_type() != device_type || acc_get_default_async() != default_async){
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