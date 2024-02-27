#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Seed for random generator; define it for consistency in tests.
#define SEED 12345
// Defining the number of test calls to simulate multiple initializations.
#define NUM_TEST_CALLS 5

#ifndef T1
// T1:init directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Attempting to initialize OpenACC runtime.
    #pragma acc init

    // After initialization, try to get the number of devices.
    // This operation requires the OpenACC runtime to be initialized.
    // If it fails, or no devices are available (returning 0), we consider that an error.
    int num_devices = acc_get_num_devices(acc_device_none);
    if(num_devices == 0){
        // In case no devices are found, mark this as an error.
        printf("Error: No devices found or acc_get_num_devices failed.\n");
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

    // Return code indicates success (0) or failure (non-zero) based on the tests conducted.
    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }

    return failcode;
}