#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int i, err = 0;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data to device
    #pragma acc data copyin(a[:N]) copy(b[:N])
    {
        // Update b in parallel
        #pragma acc update device(b[:N])
    }

    // Check that b has been updated correctly
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}