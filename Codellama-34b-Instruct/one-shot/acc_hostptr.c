#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_hostptr(void) {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * NUM_TEST_CALLS);
    int *b = (int *)malloc(sizeof(int) * NUM_TEST_CALLS);

    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc hostptr(a[0:NUM_TEST_CALLS])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < NUM_TEST_CALLS; i++) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = test_acc_hostptr();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}