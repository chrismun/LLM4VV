#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 1e-6
#define SEED 12345

int test_private_clause(int n, int m, int k) {
    int err = 0;
    int i, j, x;
    real_t *a = (real_t *)malloc(n * m * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * m * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * m * sizeof(real_t));

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            a[i * m + j] = rand() / (real_t)(RAND_MAX / 10);
            b[i * m + j] = 0;
            c[i * m + j] = 0;
        }
    }

    #pragma acc parallel num_gangs(n) num_workers(m) vector_length(k) private(a, b, c)
    {
        #pragma acc loop gang
        for (i = 0; i < n; i++) {
            #pragma acc loop worker
            for (j = 0; j < m; j++) {
                #pragma acc loop vector
                for (x = 0; x < k; x++) {
                    b[i * m + j] += a[i * m + j] * c[i * m + j];
                }
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (fabs(b[i * m + j] - a[i * m + j] * c[i * m + j]) > PRECISION) {
                err++;
            }
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = test_private_clause(10, 10, 10);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    failed = test_private_clause(10, 10, 100);
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    failed = test_private_clause(10, 100, 10);
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    failed = test_private_clause(10, 100, 100);
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    failed = test_private_clause(100, 10, 10);
    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    failed = test_private_clause(100, 10, 100);
    if (failed != 0) {
        failcode = failcode + (1 << 5);
    }

    failed = test_private_clause(100, 100, 10);
    if (failed != 0) {
        failcode = failcode + (1 << 6);
    }

    failed = test_private_clause(100, 100, 100);
    if (failed != 0) {
        failcode = failcode + (1 << 7);
    }

    return failcode;
}