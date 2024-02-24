#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000

int main() {
    int *a, *b, *c;
    int i;

    // Allocate memory for vectors a, b, and c
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));
    c = (int*)malloc(N * sizeof(int));

    // Initialize vectors a and b
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition using OpenACC
    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N]) async(1)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for the kernels to finish
    #pragma acc wait

    // Check the results
    for (i = 0; i < N; i++) {
        if (c[i] != 2 * i) {
            printf("Error at index %d: %d != %d\n", i, c[i], 2 * i);
            return 1;
        }
    }

    printf("Success!\n");
    return 0;
}