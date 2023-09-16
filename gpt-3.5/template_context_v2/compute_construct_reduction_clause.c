#include "acc_testsuite.h"
#ifndef T1
// T1: compute construct reduction clause, V: 2.7-3.3
int test1() {
    int err = 0;
    const int N = 1000;
    int a[N], b[N], c[N], sum = 0, sum_acc = 0;

    srand(SEED);

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 10 + 1;
        b[i] = rand() % 10 + 1;
    }

    // Compute sum on host
    for (int i = 0; i < N; i++) {
        sum += a[i] * b[i];
    }

    // Compute sum on device using OpenACC
    #pragma acc data copyin(a, b) copyout(c)
    #pragma acc kernels loop reduction(+:sum_acc)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] * b[i];

        // Explicitly reduction to update sum_acc on device
        sum_acc += c[i];
    }

    // Check if the sum is computed correctly on the device
    if (sum != sum_acc) {
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
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}