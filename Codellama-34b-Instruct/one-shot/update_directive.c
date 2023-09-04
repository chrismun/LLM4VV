#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define PRECISION 0.0001

int test_update(int n, int *a, int *b) {
    int err = 0;
    int i;

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (i = 0; i < n; i++) {
                b[i] = a[i] + 1;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (fabs(b[i] - (a[i] + 1)) > PRECISION) {
            err++;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    int n = 1000;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    failed = test_update(n, a, b);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    free(a);
    free(b);

    return failcode;
}