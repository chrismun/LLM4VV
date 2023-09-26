#include "acc_testsuite.h"

#ifndef T1
// T1: runtime, data, executable-data, construct-independent, V: 2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    size_t bytes = /* calculate the number of bytes for allocation */ ;

    // Allocate memory on the device using acc_malloc
    d_void* ptr = acc_malloc(bytes);

    // Check if the allocation was successful
    if (ptr == NULL) {
        err = 1;
    }

    // Free the allocated memory on the device
    acc_free(ptr);

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