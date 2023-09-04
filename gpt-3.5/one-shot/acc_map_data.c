#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 10

int main() {
    int i;
    int *a, *b, *c;

    a = (int *)malloc(N*sizeof(int));
    b = (int *)malloc(N*sizeof(int));
    c = (int *)malloc(N*sizeof(int));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 2*i;
        c[i] = 0;
    }

    #pragma acc data map(a[:N],b[:N]) // Map the arrays a and b
    {
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    printf("Results:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    free(a);
    free(b);
    free(c);

    return 0;
}