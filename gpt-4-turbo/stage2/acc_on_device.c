#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Begin of Test for acc_on_device
int test_acc_on_device() {
    int err = 0;
    srand(SEED);

    // Test on the host
    if (!acc_on_device(acc_device_host)) {
        printf("Error: acc_on_device(acc_device_host) should return true when running on the host.\n");
        err++;
    }

    if (acc_on_device(acc_device_not_host)) {
        printf("Error: acc_on_device(acc_device_not_host) should return false when running on the host.\n");
        err++;
    }

    // Initiating a parallel region to test execution on the device
    #pragma acc parallel
    {
        if (!acc_on_device(acc_device_not_host)) {
            printf("Error: acc_on_device(acc_device_not_host) should return true inside an accelerator region if there is an accelerator.\n");
            err++;
        }
    }

    return err;
}
// End of Test for acc_on_device

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_on_device();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Fail code: %d\n", failcode);
    }

    return failcode;
}