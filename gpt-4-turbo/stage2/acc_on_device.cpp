#include <iostream>
#include <openacc.h>
#include <cstdlib>

// Mock-up for the acc_testsuite.h header content, adjust as needed.
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:acc on device, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test if running on the host CPU
    if (acc_on_device(acc_device_host) == 0) {
        // Should return true (1) when asked if this is running on host outside of a compute region
        std::cerr << "Error: acc_on_device did not recognize host CPU outside of compute region." << std::endl;
        err++;
    }

    // Test if running on host is recognized as not running on a non-host device
    if (acc_on_device(acc_device_not_host) != 0) {
        // Should return false (0) when asked if this is running on a non-host device
        std::cerr << "Error: acc_on_device improperly recognized a non-host device while running on host." << std::endl;
        err++;
    }

    #pragma acc parallel
    {
        // Inside a compute region; the behavior should be the opposite.
        if (acc_on_device(acc_device_host) != 0) {
            std::cerr << "Error: acc_on_device did not recognize execution on an accelerator." << std::endl;
            err++;
        }
        if (acc_on_device(acc_device_not_host) == 0) {
            std::cerr << "Error: acc_on_device did not recognize that it's not on the host in a compute region." << std::endl;
            err++;
        }
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