#include "acc_testsuite.h"
#ifndef T1
// T1: acc wait any, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        int a[N], b[N];
        for (int i = 0; i < N; i++) {
            a[i] = rand() % 10;
            b[i] = rand() % 10;
        }

        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                a[i] += 1;
            }

            #pragma acc loop wait
            for (int i = 0; i < N; i++) {
                b[i] *= a[i];
            }
        }

        #pragma acc wait any

        for (int i = 0; i < N; i++) {
            if (b[i] != (a[i] * 2)) {
                err = 1;
                break;
            }
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
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}