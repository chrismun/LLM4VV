#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_loop_device_type(int n) {
    int err = 0;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels loop device_type(acc_device_host)
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < n; i++) {
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
        failed = test_loop_device_type(i);
        if (failed != 0) {
            failcode = failcode + (1 << i);
        }
    }

    return failcode;
}