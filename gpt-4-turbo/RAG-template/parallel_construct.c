#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:parallel,V:2.7-3.3
int test1() {
    int err = 0;
    const int size = 10000;
    int *a = (int *)malloc(size * sizeof(int));
    int correct = 5;

    // Initialize OpenACC device
    acc_init(acc_device_default);

    // Parallel construct to initialize array 'a'
    #pragma acc parallel loop
    for (int i = 0; i < size; ++i) {
        a[i] = correct;
    }

    // Check results
    for (int i = 0; i < size; ++i) {
        if (a[i] != correct) {
            err++;
        }
    }

    // Cleanup
    free(a);
    acc_shutdown(acc_device_default);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }
    return failcode;
}