#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

// Test function to verify acc_on_device functionality
int test_acc_on_device(){
    int err = 0;
    srand(SEED);

    // Checking execution on the host device
    if (!acc_on_device(acc_device_host)) {
        printf("Error: acc_on_device(acc_device_host) should return true when executed on the host.\n");
        err++;
    }

    // Test the negation for acc_device_not_host, expected to be false when on the host
    if (acc_on_device(acc_device_not_host)) {
        printf("Error: acc_on_device(acc_device_not_host) should return false when executed on the host.\n");
        err++;
    }

    // Attempting to execute a simple parallel region, and inside, checking acc_device_nvidia (as an example)
    #pragma acc parallel
    {
        if(acc_on_device(acc_device_nvidia)) {
            printf("Executing on NVIDIA device as expected.\n");
        } else {
            printf("Not executing on an NVIDIA device, or no NVIDIA device available.\n");
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_on_device();
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