#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_shutdown(int *a, int *b, int n) {
    int err = 0;
    int i;

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
        {
            #pragma acc loop
            for (i = 0; i < n; i++) {
                b[i] = a[i];
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            err++;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[10];

    failed = test_shutdown(a, b, 10);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}