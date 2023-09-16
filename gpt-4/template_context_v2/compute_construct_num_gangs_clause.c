#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    #pragma acc parallel num_gangs(10)
    {
        if (acc_on_device(acc_device_not_host)){
            if (acc_get_num_threads(acc_threadgang) != 10){
                err = 1;
            }
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