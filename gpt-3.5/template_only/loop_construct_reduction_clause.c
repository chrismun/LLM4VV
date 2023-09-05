#include "acc_testsuite.h"

#ifndef T1
// T1: runtime, data, executable-data, construct-independent, V:2.0-2.7
int test1() {
    int err = 0;
    int sum = 0;

    // Create a vector of size N
    int N = 1000;
    int *data = (int *)malloc(N * sizeof(int));

    // Initialize the vector
    for (int i = 0; i < N; ++i) {
        data[i] = i;
    }

    // Compute the sum of the vector using OpenACC reduction clause
    #pragma acc data copyin(data[0:N]) reduction(+:sum)
    #pragma acc kernels
    {
       #pragma acc loop
       for (int i = 0; i < N; ++i) {
           sum += data[i];
       }
    }

    // Verify the correctness of the result
    int expectedSum = N * (N-1) / 2;
    if (sum != expectedSum) {
        err = 1;
    }

    free(data);

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