#include "acc_testsuite.h"
#ifndef T2
// T2:parallel,vector,vector_length,V:1.0-2.7
int test2() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 100);
        b[x] = rand() / (real_t)(RAND_MAX / 100);
        c[x] = 0;
    }

    // Example vector_length is set to 128. Adjust according to the target architecture and testing needs.
    #pragma acc parallel copyin(a[0:n], b[0:n]) copyout(c[0:n]) vector_length(128)
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x) {
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs((a[x] + b[x]) - c[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);
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