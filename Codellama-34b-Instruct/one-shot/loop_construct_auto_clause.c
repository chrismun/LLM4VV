#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int test_loop_auto(int n) {
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % 100;
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels loop auto(x)
        for (int x = 0; x < n; ++x) {
            b[x] = a[x];
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
        failed = test_loop_auto(100);
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}