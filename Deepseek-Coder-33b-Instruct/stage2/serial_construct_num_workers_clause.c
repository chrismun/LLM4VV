#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc loop independent
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for (i = 0; i < N; i++) {
        if (c[i] != 2 * i) {
            printf("Error at index %d: %d != %d\n", i, c[i], 2 * i);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}