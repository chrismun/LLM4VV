#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc parallel loop gang(static:1)
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Gang clause test passed\n");
    return 0;
}