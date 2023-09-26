#include "acc_testsuite.h"
#include <stdbool.h>

#ifndef T1
/*T1:parallel construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    bool isOffloading;

    #pragma acc parallel copy(isOffloading)
    {
        #pragma acc on_device(acc_device_not_host)
        {
            isOffloading = true;
        }
        #pragma acc on_device(acc_device_host)
        {
            isOffloading = false;
        }
    }

    // if the offloading fails, err will NOT remain 0
    if( !isOffloading){
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