#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define PRECISION 0.0001

int test_atomic_add(int *a, int *b, int n) {
    int err = 0;
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                #pragma acc atomic update
                a[i] += b[i];
            }
        }
    }
    return err;
}

int test_atomic_sub(int *a, int *b, int n) {
    int err = 0;
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                #pragma acc atomic update
                a[i] -= b[i];
            }
        }
    }
    return err;
}

int test_atomic_mul(int *a, int *b, int n) {
    int err = 0;
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                #pragma acc atomic update
                a[i] *= b[i];
            }
        }
    }
    return err;
}

int test_atomic_div(int *a, int *b, int n) {
    int err = 0;
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                #pragma acc atomic update
                a[i] /= b[i];
            }
        }
    }
    return err;
}

int main() {
    int failcode = 0;
    int failed;

    int a[NUM_TEST_CALLS];
    int b[NUM_TEST_CALLS];

    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        a[i] = i;
        b[i] = i;
    }

    failed = test_atomic_add(a, b, NUM_TEST_CALLS);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    failed = test_atomic_sub(a, b, NUM_TEST_CALLS);
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    failed = test_atomic_mul(a, b, NUM_TEST_CALLS);
    if (failed != 0) {
        failcode = failcode + (1 << 2);
    }

    failed = test_atomic_div(a, b, NUM_TEST_CALLS);
    if (failed != 0) {
        failcode = failcode + (1 << 3);
    }

    return failcode;
}