#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>

#ifndef T1
// T1: acc memcpy from device, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(time(NULL));

    // Initialize data on the host
    int* host_data = (int*)malloc(sizeof(int) * DATA_SIZE);
    for (int i = 0; i < DATA_SIZE; i++) {
        host_data[i] = rand() % 100;
    }

    // Allocate and copy data to the device
    int* device_data;
    #pragma acc data create(device_data[0:DATA_SIZE])
    {
        device_data = (int*)acc_malloc(sizeof(int) * DATA_SIZE);
        if (!device_data) {
            err = 1;
        }
        #pragma acc parallel loop present(host_data[0:DATA_SIZE]) copyin(host_data[0:DATA_SIZE]) \
                                        create(device_data[0:DATA_SIZE]) copyout(device_data[0:DATA_SIZE])
        for (int i = 0; i < DATA_SIZE; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Verify data on the device
    #pragma acc data present(device_data[0:DATA_SIZE]) copyout(host_data[0:DATA_SIZE])
    {
        #pragma acc parallel loop present(device_data[0:DATA_SIZE]) copyin(device_data[0:DATA_SIZE]) \
                                        copyout(host_data[0:DATA_SIZE])
        for (int i = 0; i < DATA_SIZE; i++) {
            if (device_data[i] != host_data[i]) {
                err = 1;
                break;
            }
        }
    }

    // Free memory on the device
    acc_free(device_data);

    // Free memory on the host
    free(host_data);

    return err;
}
#endif

int main() {
    int failcode = 0;

    #ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    #endif

    return failcode;
}