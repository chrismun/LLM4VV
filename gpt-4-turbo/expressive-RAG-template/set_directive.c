#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Attempt to set the device number to a known value (0 for simplicity)
    int device_num_to_test = 0;
    #pragma acc set device_num(device_num_to_test)

    // Verify if the device number was set correctly
    int current_device = acc_get_device_num(acc_get_device_type());
    if (current_device != device_num_to_test) {
        err += 1;
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