#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
/*T1:acc get device num,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int deviceType = acc_host; // Assume the testing on host device
    int deviceNum = acc_get_device_num(deviceType);

    if(deviceNum < -1){
        err = 1;  // As per specification, a device number should be -1 or more if a device of a given type exists.
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