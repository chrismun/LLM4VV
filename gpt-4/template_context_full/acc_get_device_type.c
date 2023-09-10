#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>

#ifndef T1
/*T1:acc get device type,V:2.0-2.7*/
int test1(){
    int err = 0;
    acc_device_t deviceType;

    #pragma acc parallel
    {
        deviceType = acc_get_device_type();
    }

    if(deviceType == acc_device_none){
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