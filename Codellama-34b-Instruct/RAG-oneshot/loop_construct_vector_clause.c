#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: vector clause with parallel construct
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: vector clause with kernels construct
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}

int test1() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc parallel loop vector(a[0:n])
    for (int x = 0; x < n; ++x) {
        b[x] = a[x];
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}

int test2() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc kernels loop vector(a[0:n])
    for (int x = 0; x < n; ++x) {
        b[x] = a[x];
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}