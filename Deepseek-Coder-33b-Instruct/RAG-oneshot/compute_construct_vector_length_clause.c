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

    #pragma acc parallel loop vector_length(128)
    for (i = 0; i < N; i++) {
        b[i] = a[i];
    }

    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Verification successful\n");
    return 0;
}