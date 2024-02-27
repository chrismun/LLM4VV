#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "acc_testsuite.h" // Ensure this header file is appropriate for your setup

#ifndef T2
// T2:parallel,loop,worker,V:1.0-2.7
int test2() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_parallel = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_seq = (real_t *)malloc(n * sizeof(real_t));

    // Initializing the array with random values
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b_parallel[x] = 0;
        b_seq[x] = 0;
    }

    // Parallel calculation using OpenACC worker clause
    #pragma acc parallel copyin(a[0:n]) copyout(b_parallel[0:n])
    {
        #pragma acc loop worker
        for (int x = 0; x < n; ++x) {
            b_parallel[x] = sqrt(a[x]); // An example operation
        }
    }

    // Sequential calculation for verification
    for (int x = 0; x < n; ++x) {
        b_seq[x] = sqrt(a[x]);
    }

    // Verifying the results
    for (int x = 0; x < n; ++x) {
        if (fabs(b_parallel[x] - b_seq[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b_parallel);
    free(b_seq);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T2
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test2();
    }
    if (failed != 0) {
        failcode += (1 << 1); // Updating failcode for test2 failure
    }
#endif
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }
    return failcode;
}