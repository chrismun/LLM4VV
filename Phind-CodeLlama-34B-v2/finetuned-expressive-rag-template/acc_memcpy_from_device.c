#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int *a, *b, i, err = 0;
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:N])
    #pragma acc enter data create(b[0:N])

    #pragma acc kernels present(a[0:N], b[0:N])
    {
        #pragma acc loop
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    #pragma acc update host(b[0:N])

    #pragma acc exit data delete(a[0:N])
    #pragma acc exit data copyout(b[0:N])

    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}