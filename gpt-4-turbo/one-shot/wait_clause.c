#include "acc_testsuite.h"
#ifndef T1
//T1:async,wait,V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    int async1 = 1;
    int async2 = 2;

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels async(async1) copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }

        // Introducing another separate asynchronous operation
        #pragma acc update async(async2) self(b[0:n])

        #pragma acc wait(async1, async2)
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
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