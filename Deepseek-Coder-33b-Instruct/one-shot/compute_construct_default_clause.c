#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc parallel loop default(present)
        for (int i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}