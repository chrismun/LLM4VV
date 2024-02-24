#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000
#define VECTOR_LENGTH 128

int main() {
    int *a, *b, *c;
    int i;

    // Allocate memory for vectors a, b, and c
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));
    c = (int*)malloc(N * sizeof(int));

    // Initialize vectors a and b
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition using OpenACC
    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N]) vector_length(VECTOR_LENGTH)
    for(i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Check the results
    for(i = 0; i < N; i++) {
        if(c[i] != 2*i) {
            printf("Error at index %d: expected %d, got %d\n", i, 2*i, c[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}