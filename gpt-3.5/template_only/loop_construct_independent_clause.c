#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int sum = 0;
    int data[N];
    for (int i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    #pragma acc parallel loop independent
    for (int i = 0; i < N; i++) {
        sum += data[i];
    }

    int expected_sum = N * (N - 1) / 2;
    if (sum != expected_sum) {
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
        failed += test1();
    }
    if (failed != 0) {
        failcode |= 1 << 0;
    }
#endif

    return failcode;
}