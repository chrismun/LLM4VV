#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 1234

int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t dev_type = rand() % acc_get_num_devices(acc_device_default);
    acc_set_device_type(dev_type);

    if (acc_get_device_type() != dev_type){
        err = 1;
        printf("acc_set_device_type failed: expected %d, got %d\n", dev_type, acc_get_device_type());
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}