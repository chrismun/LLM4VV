#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_wait_async(void) {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:10])
    {
        #pragma acc kernels async(1)
        {
            #pragma acc loop
            for (int i = 0; i < 10; i++) {
                b[i] = a[i];
            }
        }
    }

    #pragma acc wait async(1)

    for (int i = 0; i < 10; i++) {
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

    failed = test_acc_wait_async();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}