#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize data
    int size = 100;
    int *data_host = (int *)malloc(size * sizeof(int));
    int *data_dev = (int *)acc_malloc(size * sizeof(int));

    // Copy data from host to device
    acc_memcpy_to_device(data_dev, data_host, size * sizeof(int));
        
    // Validate the data
    for (int i = 0; i < size; i++) {
        if (data_dev[i] != data_host[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    acc_free(data_dev);
    free(data_host);

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