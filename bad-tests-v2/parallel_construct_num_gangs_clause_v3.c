#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() == acc_device_none){
        return err;
    }
    #pragma acc parallel num_gangs(2222, 1)
    {
        if (acc_get_device_type() == acc_device_host){
            if (acc_get_num_gangs(1) != acc_get_device_num_gangs(1)){
                err += 1;
            }
            if (acc_get_num_gangs(1)*2222 == acc_get_device_num_gangs(1)){
                err += 1;
            }
        }
        #pragma acc loop gang
        for (int x = 0; x < 10; ++x){
            ;
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