#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int *a, *b;
    int fail = 0;

    a = (int*)malloc(N * sizeof(int));
    b = (int*)acc_malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    acc_memcpy_to_device(b, a, N * sizeof(int));

    for (i = 0; i < N; i++) {
        if (a[i] != i) {
            fail = 1;
            break;
        }
    }

    acc_free(b);
    free(a);

    return fail;
}