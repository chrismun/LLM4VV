#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int *data = (int *)malloc(10 * sizeof(int));
    if (data == NULL) {
        return 1;
    }

    // Initialize data on the host
    for (int i = 0; i < 10; ++i) {
        data[i] = i;
    }

    // Create a device copy of data using the enter data directive
    #pragma acc enter data copyin(data[0:10])

    // TODO: Add code to verify correctness of the enter data directive

    // Delete the device copy of data using the exit data directive
    #pragma acc exit data delete(data)

    free(data);

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