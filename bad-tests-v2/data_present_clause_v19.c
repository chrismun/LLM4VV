#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int *arr = (int*)malloc(N * sizeof(int));

    #pragma acc data present(arr[0:N])
    {
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i) {
            arr[i] = i;
        }
    }

    for (int i = 0; i < N; ++i) {
        if (arr[i] != i) {
            err = 1;
            break;
        }
    }

    free(arr);

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