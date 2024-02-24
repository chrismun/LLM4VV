#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop vector_length(128)
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (c[i] != 2 * i) {
            printf("Error at index %d: %d != %d\n", i, c[i], 2 * i);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}