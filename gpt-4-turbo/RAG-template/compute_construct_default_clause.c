#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: {compute_construct, default_clause}, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int *a_host = (int*)malloc(N * sizeof(int));
    int *a_device;
    int total = 0;

    for (int i = 0; i < N; ++i) {
        a_host[i] = rand() % 100;  // Populate with some values
        total += a_host[i];
    }

    // Allocate device memory for array
    a_device = (int *)acc_malloc(N * sizeof(int));
    acc_memcpy_to_device(a_device, a_host, N * sizeof(int));

    int sum = 0;

    #pragma acc parallel loop default(none) copyout(sum) deviceptr(a_device)
    for (int i = 0; i < N; ++i) {
        sum += a_device[i];
    }

    // Verify the results
    if (sum != total) {
        err += 1;
    }

    // Cleanup
    acc_free(a_device);
    free(a_host);

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
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}