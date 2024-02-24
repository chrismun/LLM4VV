#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N], c[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Compute with OpenACC
    #pragma acc parallel loop copyin(a[0:N], b[0:N]) copyout(c[0:N])
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Verify results
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d: c[%d] = %d, expected %d\n", i, i, c[i], a[i] + b[i]);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}