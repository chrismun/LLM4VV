#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N])
    {
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

    printf("All tests passed.\n");
    return 0;
}