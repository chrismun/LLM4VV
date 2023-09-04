#include "acc_testsuite.h"

#ifndef T1
//T1:runtime/get_property/omp/1.0/nil/0-9,0-9
int test1(){
    int err = 0;
    int num_gangs = 0;
    int num_workers = 0;

    acc_get_property(acc_device_nvidia, acc_property_num_gangs, &num_gangs);
    acc_get_property(acc_device_nvidia, acc_property_num_workers, &num_workers);

    if (num_gangs <= 0 || num_workers <= 0){
        err += 1;
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