#include "acc_testsuite.h"
#ifndef T1
// T1: attachment counter, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc enter data copyin(A[0:N])

    int *A = acc_malloc(N * sizeof(int));
    if (A == NULL) {
        err = 1;
    }

    #pragma acc exit data delete(A)

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