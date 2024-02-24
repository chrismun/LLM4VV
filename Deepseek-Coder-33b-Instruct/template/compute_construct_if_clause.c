#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, a[N], b[N], c[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    // Compute on GPU
    #pragma acc kernels copyin(a[0:N], b[0:N]), copyout(c[0:N])
    for (i = 0; i < N; i++) {
        if (i % 2 == 0) {
            c[i] = a[i] + b[i];
        } else {
            c[i] = a[i] - b[i];
        }
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (i % 2 == 0 && c[i] != a[i] + b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        } else if (i % 2 != 0 && c[i] != a[i] - b[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("All tests passed\n");
    return 0;
}