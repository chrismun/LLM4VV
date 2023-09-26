#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int* host_array = (int*)malloc(10 * sizeof(int));
    int* device_array = acc_malloc(10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
        device_array[i] = 0;
    }

    acc_memcpy_from_device(host_array, device_array, 10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
        if (host_array[i] != i) {
            err = 1;
            break;
        }
    }

    acc_free(device_array);
    free(host_array);

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