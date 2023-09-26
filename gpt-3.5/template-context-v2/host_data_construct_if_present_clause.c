#include "acc_testsuite.h"
#ifndef T1
// T1: host_data construct if_present clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(N * sizeof(int));
    int *b = (int *)malloc(N * sizeof(int));

    if (a == NULL || b == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc data copyin(a[0:N]) if_present(a)
    {
        // Perform some computations
        for (int i = 0; i < N; ++i) {
            a[i] += 2;
        }
    }

    // Verify if the computations were successful
    for (int i = 0; i < N; ++i) {
        if (a[i] != (b[i] + 2)) {
            err = 1;
            break;
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
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}