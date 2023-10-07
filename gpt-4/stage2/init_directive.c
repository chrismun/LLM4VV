#include "acc_testsuite.h"
#include <openacc.h>
#include <stdio.h>

#ifndef T1
/* T1:init directive, V:2.0-2.7 */
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize the device
    #pragma acc init 

    if (!acc_get_num_devices(acc_device_default)) {
        printf("Device initialization failed\n");
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        printf("Test1 failed\n");
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}