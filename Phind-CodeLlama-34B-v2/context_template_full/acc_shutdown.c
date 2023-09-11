#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:acc shutdown,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    acc_init(acc_device_default);

    acc_shutdown(acc_device_default);

    if (acc_get_device_type() != acc_device_none){
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