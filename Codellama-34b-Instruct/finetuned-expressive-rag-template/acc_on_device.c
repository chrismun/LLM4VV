#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 123
#define NUM_TEST_CALLS 1

#ifndef T1
//T1:acc on device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = acc_get_device_type(acc_device_host);
    if (acc_on_device(device_type) != 1) {
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