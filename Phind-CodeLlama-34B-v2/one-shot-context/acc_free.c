#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    float *a, *b;
    int i;

    a = (float *)malloc(N * sizeof(float));
    b = (float *)acc_malloc(N * sizeof(float));

    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    acc_memcpy(b, a, N * sizeof(float));

    acc_free(b);

    free(a);

    return 0;
}