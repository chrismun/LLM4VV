#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc parallel loop
    for(i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    for(i = 0; i < N; i++) {
        if(c[i] != 2*i) {
            printf("Error at index %d: %d != %d\n", i, c[i], 2*i);
            return 1;
        }
    }

    printf("All elements are correct!\n");
    return 0;
}