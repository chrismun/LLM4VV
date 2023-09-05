#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

void acc_wait_test() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    #pragma acc parallel loop gang async(1)
    for (int i = 0; i < n; ++i) {
        a[i] = i;
    }

    #pragma acc parallel loop gang async(2)
    for (int i = 0; i < n; ++i) {
        b[i] = 2 * a[i];
    }

    #pragma acc wait(1)

    #pragma acc parallel loop gang async(3)
    for (int i = 0; i < n; ++i) {
        b[i] += a[i];
    }

    #pragma acc wait(2,3)

    for (int i = 0; i < n; ++i) {
        printf("b[%d] = %d\n", i, b[i]);
    }

    free(a);
    free(b);
}

int main() {
    acc_wait_test();
    return 0;
}