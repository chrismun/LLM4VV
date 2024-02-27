#include "acc_testsuite.h"
#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[100];
    real_t * b = new real_t[100];
    real_t * c = new real_t[100];

    for (int x = 0; x < 100; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 10;
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:100]) copyout(c[0:100])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 100; ++x) {
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < 100; ++x) {
        if (fabs(c[x] - (a[x] + 10)) > PRECISION) {
            err = 1;
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