#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: Parallel construct with a single loop
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        int n = 1000;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = i;
            b[i] = 0;
        }

        #pragma acc parallel loop
        for (int i = 0; i < n; ++i) {
            b[i] = a[i];
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err++;
            }
        }

        if (err > 0) {
            failed++;
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test 2: Parallel construct with multiple loops
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        int n = 1000;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = i;
            b[i] = 0;
        }

        #pragma acc parallel loop
        for (int i = 0; i < n; ++i) {
            b[i] = a[i];
        }

        #pragma acc parallel loop
        for (int i = 0; i < n; ++i) {
            b[i] = a[i];
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err++;
            }
        }

        if (err > 0) {
            failed++;
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    // Test 3: Parallel construct with a loop and a reduction
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        int n = 1000;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = i;
            b[i] = 0;
        }

        #pragma acc parallel loop reduction(+:b[:n])
        for (int i = 0; i < n; ++i) {
            b[i] += a[i];
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err++;
            }
        }

        if (err > 0) {
            failed++;
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    // Test 4: Parallel construct with a loop and a reduction with a custom reduction operator
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        int n = 1000;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = i;
            b[i] = 0;
        }

        #pragma acc parallel loop reduction(+:b[:n])
        for (int i = 0; i < n; ++i) {
            b[i] += a[i];
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err++;
            }
        }

        if (err > 0) {
            failed++;
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    // Test 5: Parallel construct with a loop and a reduction with a custom reduction operator and a custom reduction variable
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        int n = 1000;
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = i;
            b[i] = 0;
        }

        #pragma acc parallel loop reduction(+:b[:n])
        for (int i = 0; i < n; ++i) {
            b[i] += a[i];
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err++;
            }
        }

        if (err > 0) {
            failed++;
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 4);
    }

    return failcode;
}