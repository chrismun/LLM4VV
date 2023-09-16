#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024
#define PRECISION 0.0001

int validate_acc_memcpy_device() {
    int err = 0;
    real_t *a = (real_t *)malloc(N * sizeof(real_t));
    real_t *b = (real_t *)malloc(N * sizeof(real_t));

    for (int x = 0; x < N; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc kernels
    {
        #pragma acc loop
        for (int x = 0; x < N; ++x) {
            b[x] = a[x];
        }
    }

    #pragma acc update self(b[0:N])

    for (int x = 0; x < N; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:N])
    #pragma acc exit data delete(b[0:N])

    return err;
}

int main() {
    int failed = 0;
    for (int x = 0; x < 10; ++x) {
        failed = failed + validate_acc_memcpy_device();
    }
    if (failed != 0) {
        printf("Test failed\n");
    } else {
        printf("Test passed\n");
    }
    return 0;
}