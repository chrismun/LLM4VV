#include "acc_testsuite.h"

#ifndef T1
/* T1: acc delete, V:2.0-2.7 */
int test1() {
    int err = 0;
    int* h_data;
    size_t bytes = sizeof(int);

    h_data = (int*)malloc(bytes);
    *h_data = 15;

    /* Place data on device */
    acc_copyin((void*)h_data, bytes);

    /* Delete data from device */
    acc_delete((void*)h_data, bytes);

    /* Data should now not be present in the device */
    if (acc_is_present((void*)h_data, bytes)) {
        err = 1;
    }

    free(h_data);

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