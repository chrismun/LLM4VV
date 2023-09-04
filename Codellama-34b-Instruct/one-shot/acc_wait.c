#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_wait(void) {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:10])
    {
        #pragma acc kernels copyout(b[0:10])
        {
            #pragma acc loop
            for (int i = 0; i < 10; i++) {
                b[i] = a[i];
            }
        }
    }

    #pragma acc wait

    for (int i = 0; i < 10; i++) {
        if (b[i] != a[i]) {
            err++;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = failed + test_acc_wait();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}