#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int test_cache(int n, int *a, int *b) {
    int err = 0;

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels cache(a[0:n])
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

    int n = 100;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = x;
        b[x] = 0;
    }

    failed = test_cache(n, a, b);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    free(a);
    free(b);

    return failcode;
}