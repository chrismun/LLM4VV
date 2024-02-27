#include "acc_testsuite.h"
#ifndef T2
// T2:data,attach,construct,V:1.0-2.7
int test2() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *) malloc(n * sizeof(real_t));
    real_t *attached_a;

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t) (RAND_MAX / 10);
    }

    #pragma acc enter data create(a[0:n])
    attached_a = a;
    #pragma acc data attach(attached_a[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x) {
            attached_a[x] = attached_a[x] + 1;
        }
    }
    #pragma acc exit data copyout(a[0:n])

    for (int x = 0; x < n; ++x) {
        if (fabs(a[x] - (rand() / (real_t) (RAND_MAX / 10) + 1)) > PRECISION) {
            err += 1;
        }
    }

    free(a);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}