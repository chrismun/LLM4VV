#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int i;
    int *a, *b;
    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));

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

    #pragma acc exit data copyout(b[0:N]) delete(a[0:N])

    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            printf("Test failed at index %d: %d != %d\n", i, a[i], b[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}