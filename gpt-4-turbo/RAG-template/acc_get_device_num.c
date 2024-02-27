#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Function to test acc_get_device_num
int test1(){
    int err = 0;
    srand(SEED);

    // Testing with a device type that should be present, assuming a GPU is present
    int gpu_device_num = acc_get_device_num(acc_device_nvidia);
    if(gpu_device_num < 0){
        printf("No NVIDIA GPUs found. Is CUDA installed and configured correctly?\n");
        err++;
    }

    // Testing with a device type that is unlikely to be supported to ensure it returns -1
    int non_existent_device_num = acc_get_device_num(acc_device_none);
    if(non_existent_device_num != -1){
        printf("Expected -1 for unsupported device type, got: %d\n", non_existent_device_num);
        err++;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }

    return failcode;
}