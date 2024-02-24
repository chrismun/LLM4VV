#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc parallel num_workers(4) copy(a[0:N], b[0:N])
    {
        #pragma acc loop
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for (i = 0; i < N; i++) {
        printf("b[%d] = %d\n", i, b[i]);
    }

    free(a);
    free(b);

    return 0;
}