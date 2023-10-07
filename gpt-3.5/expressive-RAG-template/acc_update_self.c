#include "acc_testsuite.h"
#ifndef T1
// T1: acc update self, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *A = (int *)malloc(N * sizeof(int));
    int *A_host = (int *)malloc(N * sizeof(int));

    // Initialize A on the host
    for (int i = 0; i < N; ++i) {
        A_host[i] = 0;
    }

    // Copy A_host to the device
    #pragma acc enter data copyin(A[0:N])

    // Perform update on the device
    #pragma acc update self(A[0:N])

    // Copy A from the device to the host
    #pragma acc exit data copyout(A[0:N])

    // Verify the correctness
    for (int i = 0; i < N; ++i) {
        if (A[i] != A_host[i]) {
            err = 1;
            break;
        }
    }

    free(A);
    free(A_host);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}