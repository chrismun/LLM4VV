#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

#ifndef T1
//T1:acc get num devices,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_devices = acc_get_num_devices(acc_device_default);

    if (num_devices <= 0){
        err = 1;
        printf("Test failed: No devices available.\n");
    }
    else {
        printf("Number of available devices: %d\n", num_devices);
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