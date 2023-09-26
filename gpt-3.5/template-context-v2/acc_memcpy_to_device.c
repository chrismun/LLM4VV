#include "acc_testsuite.h"
#ifndef T1
// T1:acc memcpy to device,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    size_t n = 100;
    int *host_array = (int *)malloc(sizeof(int) * n);
    int *device_array = (int *)malloc(sizeof(int) * n);

    // Initialize host_array
    for (size_t i = 0; i < n; i++) {
        host_array[i] = rand() % 10;
    }

    // Copy host_array to device_array using acc memcpy to device
    #pragma acc data copyin(host_array[0:n]) copy(device_array[0:n])
    {
        #pragma acc parallel loop
        for (size_t i = 0; i < n; i++) {
            device_array[i] = host_array[i];
        }
    }

    // Verify the correctness of the memcpy operation
    for (size_t i = 0; i < n; i++) {
        if (device_array[i] != host_array[i]) {
            err = 1;
            break;
        }
    }

    free(host_array);
    free(device_array);

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