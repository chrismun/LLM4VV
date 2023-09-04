#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int test_acc_get_default_async(int async) {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:10]) copyout(b[0:10])
    {
        #pragma acc kernels async(async)
        {
            #pragma acc loop
            for (int i = 0; i < 10; i++) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        if (fabs(b[i] - a[i]) > PRECISION) {
            err++;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int i = 0; i < NUM_TEST_CALLS; i++) {
        failed = test_acc_get_default_async(i % 2);
        if (failed != 0) {
            failcode = failcode + (1 << i);
        }
    }

    if (failcode != 0) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}