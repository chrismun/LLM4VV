#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int test_wait(void) {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * NUM_TEST_CALLS);
    int *b = (int *)malloc(sizeof(int) * NUM_TEST_CALLS);

    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:NUM_TEST_CALLS])
    {
        #pragma acc kernels wait(b[0:NUM_TEST_CALLS])
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

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = test_wait();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}