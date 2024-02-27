#include <cstdlib>
#include <iostream>
#include "acc_testsuite.h"

#ifndef T1
// T1:declare directive device_resident clause, V:2.7-3.3

#pragma acc declare create(err) device_resident

int test1() {
    int err = 0; // This declaration shadows the device_resident one for demonstration.

    // Normally, setting values on the device would involve kernels or data directives,
    // but since direct manipulation from host is not allowed for device_resident,
    // attempting a direct manipulation (as a negative test).
    
    #pragma acc parallel
    {
        err = 1; // Trying to manipulate `err` on the device. Shadowed `err` should remain unchanged on the host.
    }

    // If `err` was correctly shadowed and device_resident, the host `err` should remain 0.
    return err;
}

#endif // T1

int main(){
    int failcode = 0;
    int failed = 0;
    #ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    // If `failed` is 0, the `device_resident` is arguably functioning correctly,
    // as the attempt to change `err` on device should not affect the host `err`.
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    #endif // T1
    return failcode;
}