#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:acc init,V:2.0-2.7*/
int test1(){
    int err = 0;

    acc_device_t default_device = acc_get_device_type();
    
    /* Attempt to initialize OpenACC runtime with the default device type */
    acc_init(default_device);
    
    /* Check if the OpenACC runtime is properly initialized and the correct device is selected */
    if (acc_get_device_type() != default_device){
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