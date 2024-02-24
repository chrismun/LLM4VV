#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Set the default async value to acc_async_sync
    #pragma acc set default_async(acc_async_sync)

    // Copy array a to array b in parallel
    #pragma acc parallel loop copy(a[0:N], b[0:N])
    for (i = 0; i < N; i++) {
        b[i] = a[i];
    }

    // Check that the copy was successful
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Success!\n");
    return 0;
}