#include "acc_testuite.h"
#ifndef T1
// T1:kernels,data,data-region,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t a = rand() / (real_t)(RAND_MAX / 10);
    real_t b = 0;

    #pragma acc data copyin(a)
    {
        #pragma acc present(a)
        #pragma acc kernels
        {
            b = a;
        }
    }

    err = (fabs(b - a) > PRECISION);

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