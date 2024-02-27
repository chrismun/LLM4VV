#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Adjust these values as necessary for your testing purposes
#define SEED 12345
#define PRECISION 0.0001
typedef float real_t; // Using float as real_t for simplicity

#ifndef T1
// T1:runtime,V:1.0-2.7
int test_acc_get_device_num() {
    int err = 0;

    // Selecting a random number to target a device
    int device_count = acc_get_num_devices(acc_device_not_host);
    srand(SEED);
    int target_device = rand() % device_count;

    // Setting the device and checking acc_get_device_num
    acc_set_device_num(target_device, acc_device_not_host);
    int returned_device = acc_get_device_num(acc_device_not_host);

    // Verifying if the returned device number matches the target
    if (target_device != returned_device) {
        err++;
        printf("Error: Target device (%d) does not match returned device (%d)\n", target_device, returned_device);
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test_acc_get_device_num();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
        printf("Test failed for acc_get_device_num with %d errors.\n", failed);
    }
    else {
        printf("Test passed for acc_get_device_num.\n");
    }
#endif

    return failcode;
}