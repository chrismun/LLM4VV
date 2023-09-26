#include "acc_testsuite.h"
#include <stdlib.h>

int test_deviceptr() {
    int err = 0;
    int* host_data = (int*)malloc(sizeof(int));
    int* device_data;

    *host_data = 5;

    #pragma acc data create(device_data[1])
    {
        acc_map_data( device_data, host_data, sizeof(int));

        #pragma acc parallel loop deviceptr(device_data)
        for (int i = 0; i < 1; i++) {
            device_data[i] = device_data[i] * 2;
        }
        acc_unmap_data(device_data);

        if (*host_data != 10) {
            err = 1;
        }
    }

    free(host_data);
    return err;
}

int main() {
    int failcode = 0;
    failed = 0;
    int NUM_TEST_CALLS = 10;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_deviceptr();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}