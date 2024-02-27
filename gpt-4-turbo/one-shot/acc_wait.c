#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,async,V:1.0-2.7
int test1() {
    int err = 0;
    int async1 = 1, async2 = 2;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array 'a' asynchronously on async queue 1
    #pragma acc parallel loop async(async1)
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    // Copy 'a' to 'b' utilizing another async queue to simulate computation
    #pragma acc parallel loop async(async2) copyout(b[0:n]) copyin(a[0:n])
    for (int x = 0; x < n; ++x) {
        b[x] = a[x];
    }

    // Wait for both async operations to complete
    #pragma acc wait(async1)
    #pragma acc wait(async2)

    // Verification
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

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

    if (failcode) {
        printf("FAIL: %d\n", failcode);
    } else {
        printf("PASS\n");
    }

    return failcode;
}