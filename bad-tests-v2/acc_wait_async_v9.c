#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

int test_acc_wait_async() {
    int err = 0;
    int *a, *b;

    a = (int *)malloc(NUM_ELEMENTS * sizeof(int));
    b = (int *)malloc(NUM_ELEMENTS * sizeof(int));

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:NUM_ELEMENTS]) copyout(b[0:NUM_ELEMENTS])
    {
        #pragma acc kernels async(1)
        {
            #pragma acc loop
            for (int i = 0; i < NUM_ELEMENTS; i++) {
                b[i] = a[i] * 2;
            }
        }

        #pragma acc wait async(1)
    }

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (b[i] != a[i] * 2) {
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

    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = failed + test_acc_wait_async();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}