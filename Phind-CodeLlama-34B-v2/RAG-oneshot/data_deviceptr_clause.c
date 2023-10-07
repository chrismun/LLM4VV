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

    #pragma acc data deviceptr(a, b)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            printf("Mismatch at index %d: %d != %d\n", i, a[i], b[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}