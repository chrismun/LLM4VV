#include "acc_testsuite.h"

#ifndef T1
/*T1:loop construct collapse clause,V:2.0-2.7*/
int test1() {
    int err = 0;
    srand(SEED);
    int N = 10000;
    int result[N], host_result[N];

    // Initialize input array
    for (int i = 0; i < N; i++) {
        host_result[i] = i*(i+1)/2;
        result[i] = 0;
    }

    #pragma acc parallel loop num_gangs(128), vector_length(32) \
        copyout(result[0:N]) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= i; j++) {
            result[i] += j;
        }
    }

    // Check for correctness
    for (int i = 0; i < N; i++) {
        if (host_result[i] != result[i]) {
            err = 1;
            break;
        }
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