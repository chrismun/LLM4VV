#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 1e-6

int test1() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop private(tmp)
            for (int x = 0; x < n; ++x) {
                tmp = b[x] + c[x];
                #pragma acc loop vector
                for (int i = 0; i < n; ++i) {
                    a[i] = a[i] + tmp / div;
                }
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}

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