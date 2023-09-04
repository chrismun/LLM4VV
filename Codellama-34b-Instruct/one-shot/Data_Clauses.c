#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc/acc.h>

#define NUM_TEST_CALLS 100
#define PRECISION 0.00001

int test_data_clauses(int n, real_t *a, real_t *b) {
    int err = 0;
    srand(SEED);

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
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

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int n = rand() % 1000 + 1;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = 0;
        }

        failed = test_data_clauses(n, a, b);
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }

        free(a);
        free(b);
    }

    return failcode;
}