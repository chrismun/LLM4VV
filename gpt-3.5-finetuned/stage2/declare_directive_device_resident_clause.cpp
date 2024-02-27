#include "acc_testsuite.h"
#ifndef T1
int test1() {
    int err = 0;
    srand(SEED);
    real_t* a = new real_t[n];
    real_t* b = new real_t[n];
    real_t* c = new real_t[n];

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc declare create(a[0:n]) device_resident 
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i) {
                a[i] += b[i];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - (b[x])) > PRECISION) {
            err += 1;
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