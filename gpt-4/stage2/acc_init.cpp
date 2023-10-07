#include "openacc.h"
#include "acc_testsuite.h"

#ifdef _OPENACC

#ifndef T1
/*T1:acc init,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t dev_type = acc_device_nvidia; // This can be changed depending on the device type. 

    // Initialize OpenACC Runtime
    acc_init(dev_type);

    // Now check if the init has worked properly by testing whether OpenACC is active
    // and if the active device is the same as the one we have set. 
    if(!_OPENACC || acc_get_device_type() != dev_type){
            err = 1; // if it is not the case, change err to non-zero 
    }

    return err;
}
#endif

#else

int test1(){
    return 0;
}

#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}