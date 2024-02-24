#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int a[N], b[N], c[N];
    int i, err = 0;

    // Initialize arrays
    for (i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i * 2;
    }

    // Perform vector addition
    #pragma acc kernels num_gangs(1)
    for (i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for (i = 0; i < N; ++i) {
        if (c[i] != a[i] + b[i]) {
            printf("Error at index %d: %d != %d\n", i, c[i], a[i] + b[i]);
            err = 1;
        }
    }

    return err;
}