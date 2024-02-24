#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i, err = 0;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            b[i] = a[i];
        }

        #pragma acc update self(b[0:N])
    }

    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            err++;
        }
    }

    free(a);
    free(b);

    if (err) {
        printf("Test failed with %d errors\n", err);
        return 1;
    } else {
        printf("Test passed\n");
        return 0;
    }
}