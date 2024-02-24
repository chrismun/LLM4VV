#include <stdio.h>
#include <openacc.h>

#define T1
#include "acc_testsuite.h"

int test1(){
    int err = 0;

    // Initialize OpenACC
    acc_init(acc_device_nvidia);

    // Check if device is available
    if (acc_get_num_devices(acc_device_nvidia) == 0) {
        printf("No NVIDIA GPU devices available\n");
        err = 1;
    }

    // Shutdown OpenACC
    acc_shutdown(acc_device_nvidia);

    // Check if device is still available
    if (acc_get_num_devices(acc_device_nvidia) != 0) {
        printf("NVIDIA GPU devices are still available after shutdown\n");
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

#ifdef T1
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