#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc parallel loop independent
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    for (i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}