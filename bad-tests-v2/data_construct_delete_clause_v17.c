#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int *a;
    int i;

    a = (int *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    #pragma acc enter data copyin(a[0:N])

    #pragma acc kernels present(a[0:N])
    {
        // Do some operations on the data
        #pragma acc loop
        for (i = 0; i < N; i++) {
            a[i] *= 2;
        }
    }

    #pragma acc exit data delete(a[0:N])

    for (i = 0; i < N; i++) {
        if (a[i] != i * 2) {
            printf("Test failed: a[%d] = %d, expected %d\n", i, a[i], i * 2);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}