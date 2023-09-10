#include "acc_testsuite.h"

#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a device resident variable
    int device_resident_var;

    // Initialize the device resident variable
    device_resident_var = 0;

    // Create a compute construct
    #pragma acc parallel
    {
        // Use the device resident variable in the compute construct
        device_resident_var = 1;
    }

    // Check that the device resident variable was updated
    if (device_resident_var != 1) {
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