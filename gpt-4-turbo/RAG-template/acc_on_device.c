#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// The SEED and NUM_TEST_CALLS should be defined based on your testing framework preferences.
#define SEED 123
#define NUM_TEST_CALLS 1

int test1(){
    int err = 0;
    srand(SEED);

    // Test if running on the host.
    if(acc_on_device(acc_device_host)){
        printf("Execution confirmed on the host.\n");
    } else {
        printf("Error: Execution should be on the host but is not detected as such.\n");
        err++;
    }

    // Next, attempt to offload a simple computation to an accelerator if available
    #pragma acc parallel num_gangs(1)
    {
        if(acc_on_device(acc_device_not_host)){
            printf("Execution confirmed on an accelerator device.\n");
        } else {
            err++; // Failure to detect execution on an accelerator device
        }
    }
    
    // Using acc_on_device with a specific device type, e.g., acc_device_nvidia
    #pragma acc parallel num_gangs(1) device_type(acc_device_nvidia)
    {
        if(acc_on_device(acc_device_nvidia)){
            printf("Execution confirmed on NVIDIA accelerator.\n");
        } else {
            err++; // Failure to detect execution on a NVIDIA device
        }
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
        failcode |= (1 << 0); // Set failure code
        printf("Tests failed: %d cases\n", failed);
    } else {
        printf("All tests passed successfully!\n");
    }

    return failcode;
}