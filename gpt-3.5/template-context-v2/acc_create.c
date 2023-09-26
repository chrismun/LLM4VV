#include "acc_testsuite.h"
#ifndef T1
// T1:acc create,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc data create(A[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; i++) {
            A[i] = rand() % 100;
        }
    }

    for (int i = 0; i < N; i++) {
        if (A[i] == 0)
            err = 1;
    }

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