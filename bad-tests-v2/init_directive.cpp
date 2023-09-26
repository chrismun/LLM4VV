#include "acc_testsuite.h"

#ifndef T1
//T1:init directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the runtime for the given device or devices of the given device type
    #pragma acc init device_type(device_type_list) device_num(int_expr) if(condition)

    // Check if the initialization was successful
    if (acc_get_device_type() != device_type_list[0] || acc_get_device_num() != int_expr) {
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