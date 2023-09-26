#include "acc_testsuite.h"
#include <stdbool.h>

#ifndef T1
/*T1:serial construct if clause,V:2.0-2.7*/
int test1() {
    int err = 0;
    bool isOffload = false;
    int host_array[1], device_array[1];
    
    host_array[0] = 0;
    
    #pragma acc serial copy(host_array[0]) copy(isOffload)
    {
        isOffload = acc_is_device_type(acc_device_not_host);

        #pragma acc serial if(0) copy(device_array[0])
        {
            device_array[0] = 10;
        }
    }

    // Checking if region is executed on host
    if (isOffload || device_array[0] != 10) {
        err = 1;
    }

    return err;
}
#endif

int main() {
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