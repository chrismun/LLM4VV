#include "acc_testsuite.h"
#ifndef T1
// T1:acc hostptr,V:2.7-3.3
int test1() {
    int err = 0;
    int *A, *B, *C;
    int i;

    A = (int *)malloc(N * sizeof(int));
    B = (int *)malloc(N * sizeof(int));
    C = (int *)malloc(N * sizeof(int));

    // Initialize arrays
    for (i = 0; i < N; i++) {
        A[i] = i;
        B[i] = N - i;
    }

    #pragma acc enter data copyin(A[0:N], B[0:N], C[0:N])
    #pragma acc hostptr(A, B, C)
    {
        #pragma acc parallel loop present(A, B, C)
        for (i = 0; i < N; i++) {
            C[i] = A[i] + B[i];
        }
    }
    #pragma acc exit data copyout(C[0:N])

    // Verify result
    for (i = 0; i < N; i++) {
        if (C[i] != N) {
            err = 1;
            break;
        }
    }

    free(A);
    free(B);
    free(C);

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
    return failcode;
}