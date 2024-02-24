#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000000

int main() {
    int *a, *b, *c;
    int i;

    // Allocate memory for arrays
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));
    c = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition using OpenACC
    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N])
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Success!\n");

    // Free memory
    free(a);
    free(b);
    free(c);

    return 0;
}