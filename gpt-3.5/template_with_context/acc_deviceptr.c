#include "acc_testsuite.h"

#ifndef T1
// T1: runtime, data, executable-data, construct-independent, V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize host data
    int hostData = rand();

    // Declare device data
    int* deviceData;

    // Allocate device memory
    #pragma acc enter data copyin(hostData)
    
    // Get the device pointer
    deviceData = (int*)acc_deviceptr(&hostData);

    // Check if device pointer is null
    if (deviceData == NULL) {
        err = 1;
    }

    // Exit device data
    #pragma acc exit data delete(hostData)

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}