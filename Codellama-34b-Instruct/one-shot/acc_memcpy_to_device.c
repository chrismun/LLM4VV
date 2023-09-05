#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.00001

int test_acc_memcpy_to_device(void) {
    int err = 0;
    int *a = (int *)malloc(sizeof(int) * 10);
    int *b = (int *)malloc(sizeof(int) * 10);

    for (int i = 0; i < 10; i++) {
        a[i] = i;
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

    failed = test_acc_memcpy_to_device();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}