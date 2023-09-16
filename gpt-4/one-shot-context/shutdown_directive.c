#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

int test_shutdown(int device_num) {
    int err = 0;

    // Initialize some memory on the device
    int *a = (int *)malloc(sizeof(int));
    *a = 1;

    #pragma acc enter data copyin(a[0:1]) device(device_num)

    // Shut down connection to the device
    #pragma acc shutdown device_num(device_num)

    // Try to copy data back from device - this should fail as device is shut down
    int *b = (int *)malloc(sizeof(int));
    *b = 0;
    #pragma acc exit data copyout(b[0:1]) device(device_num)

    // The value of b should be 0
    if (*b != 0) {
        err = 1;
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int err = 0;

    // Get number of devices
    int num_devices = acc_get_num_devices(acc_device_default);

    // Test shutdown on all available devices
    for (int i = 0; i < num_devices; i++) {
        err += test_shutdown(i);
    }

    if (err != 0){
        printf("Test failed with %d errors\n", err);
    }else{
        printf("Test passed\n");
    }

    return err;
}