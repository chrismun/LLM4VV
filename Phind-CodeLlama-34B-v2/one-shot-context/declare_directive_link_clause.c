#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#define N 1024

#pragma acc declare create(a) link(a)
extern real_t a[N];

int test_declare_link() {
    int i;
    int err = 0;
    real_t *a = (real_t *) malloc(N * sizeof(real_t));

    for (i = 0; i < N; i++) {
        a[i] = i * 1.0;
    }

    #pragma acc data copy(a[0:N])
    {
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            a[i] *= 2.0;
        }
    }

    for (i = 0; i < N; i++) {
        if (fabs(a[i] - (i * 1.0 * 2.0)) > PRECISION) {
            err += 1;
        }
    }

    return err;
}

int main() {
    int i;
    int err = 0;

    for (i = 0; i < NUM_TEST_CALLS; i++) {
        err += test_declare_link();
    }

    if (err != 0) {
        printf("Test failed\n");
        return 1;
    } else {
        printf("Test passed\n");
        return 0;
    }
}