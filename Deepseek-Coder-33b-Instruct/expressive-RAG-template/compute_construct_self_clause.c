#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    #pragma acc parallel loop
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop self
    for (int i = 0; i < N; i++) {
        b[i] = a[i];
    }

    free(a);
    free(b);

    return 0;
}