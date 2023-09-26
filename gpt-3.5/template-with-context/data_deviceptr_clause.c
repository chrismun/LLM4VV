#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Declare host and device pointers
    int* host_ptr;
    int* device_ptr;

    // Allocate memory for host pointer
    host_ptr = (int*)malloc(sizeof(int) * SIZE);

    // Initialize data on host
    for (int i = 0; i < SIZE; i++) {
        host_ptr[i] = rand() % 100;
    }

    // Allocate memory for device pointer
    #pragma acc enter data copyin(host_ptr[0:SIZE]) create(device_ptr[0:SIZE])

    // Assign device pointer
    device_ptr = host_ptr;

    // Perform computation on device
    #pragma acc parallel loop deviceptr(device_ptr[0:SIZE])
    for (int i = 0; i < SIZE; i++) {
        device_ptr[i] += 1;
    }

    // Update data on host
    #pragma acc update self(host_ptr[0:SIZE])

    // Verify results
    for (int i = 0; i < SIZE; i++) {
        if (host_ptr[i] != (device_ptr[i] - 1)) {
            err = 1;
            break;
        }
    }

    // Free memory
    #pragma acc exit data delete(host_ptr[0:SIZE]) delete(device_ptr[0:SIZE])
    free(host_ptr);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}