#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int i;
    int *a;
    int *b;

    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc declare create(a[0:N])
    {
        #pragma acc parallel present(a[0:N])
        {
            #pragma acc loop
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Test failed: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}