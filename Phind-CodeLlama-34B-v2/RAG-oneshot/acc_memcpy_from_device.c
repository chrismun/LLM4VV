#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024
#define PRECISION 0.0001

int validate_acc_memcpy_from_device() {
    int err = 0;
    int *a, *b;

    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));

    for (int x = 0; x < N; ++x) {
        a[x] = rand() % 100;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc kernels present(a[0:N], b[0:N])
    {
        for (int x = 0; x < N; ++x) {
            b[x] = a[x];
        }
    }

    #pragma acc exit data copyout(b[0:N])

    for (int x = 0; x < N; ++x) {
        if (abs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);

    return err;
}

int main() {
    int failed = 0;

    for (int x = 0; x < 10; ++x) {
        failed = failed + validate_acc_memcpy_from_device();
    }

    if (failed != 0) {
        printf("Test failed\n");
    } else {
        printf("Test passed\n");
    }

    return 0;
}