#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory for the device pointer
    int *dev_ptr = (int *)malloc(sizeof(int) * N);

    // Initialize the device pointer
    for (int i = 0; i < N; i++) {
        dev_ptr[i] = i;
    }

    // Create an OpenACC device pointer
    acc_deviceptr_t dev_ptr_acc = acc_deviceptr_create(dev_ptr, N * sizeof(int));

    // Verify that the device pointer is valid
    if (!acc_deviceptr_is_valid(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is executable
    if (!acc_deviceptr_is_executable(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is data-dependent
    if (!acc_deviceptr_is_data_dependent(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is construct-independent
    if (!acc_deviceptr_is_construct_independent(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is runtime-dependent
    if (!acc_deviceptr_is_runtime_dependent(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is data-dependent
    if (!acc_deviceptr_is_data_dependent(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is executable-data
    if (!acc_deviceptr_is_executable_data(dev_ptr_acc)) {
        err = 1;
    }

    // Verify that the device pointer is V:2.0-2.7
    if (!acc_deviceptr_is_V_2_0_2_7(dev_ptr_acc)) {
        err = 1;
    }

    // Free the device pointer
    free(dev_ptr);

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