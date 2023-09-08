#include "acc_testsuite.h"

#ifndef T1
//T1:acc init,V:2.7-3.3
int test1(){
    int err = 0;

    // Initialize the runtime for a specific device type and device number
    acc_init(ACC_DEVICE_TYPE_GPU, 0);

    // Do some work with the GPU
    // ...

    // Shut down the runtime for the GPU
    acc_shutdown(ACC_DEVICE_TYPE_GPU, 0);

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