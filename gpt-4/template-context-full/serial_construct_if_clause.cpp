#include "acc_testsuite.h"
#include <cstdlib>
#include <vector>

#ifndef T1
/*T1:serial construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    bool isAccelerator = false;
    srand(SEED);
    
    #pragma acc serial copy(isAccelerator) if( rand() % 2 ) 
    {
        #if _OPENACC
        isAccelerator = acc_on_device(acc_device_not_host);
        #endif
    }
   
    if(!isAccelerator){
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