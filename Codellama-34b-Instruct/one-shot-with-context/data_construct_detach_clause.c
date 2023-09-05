#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int test1(int *a, int *b, int n) {
    int err = 0;
    #pragma acc data detach(a[0:n])
    {
        #pragma acc kernels
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
    int a[NUM_TEST_CALLS];
    int b[NUM_TEST_CALLS];

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        a[x] = rand() % 100;
        b[x] = 0;
    }

    failed = test1(a, b, NUM_TEST_CALLS);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}