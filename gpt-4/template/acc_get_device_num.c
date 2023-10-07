#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

//T1: acc_get_device_num, V: OpenACC 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED); // For generating the random number

    int device_type = rand() % 2 == 0 ? acc_device_host : acc_device_nvidia; // Randomly choosing type of device.
    int device_num = rand() % acc_get_num_devices(device_type); // Choosing a valid random number for device.

    acc_set_device_num(device_num, device_type);

    // Verifying the set device number with OpenACC runtime
    if (acc_get_device_num(device_type) != device_num) {
        err = 1; // If evaluation doesn't match, set the error to 1.
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}