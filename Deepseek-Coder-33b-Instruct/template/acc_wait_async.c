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
        b[i] = i * 2;
    }

    // Perform parallel computation
    #pragma acc parallel loop
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for all devices to finish
    #pragma acc wait

    // Perform asynchronous computation
    #pragma acc parallel loop async
    for (i = 0; i < N; i++) {
        a[i] = c[i] * 2;
    }

    // Wait for asynchronous computation to finish
    #pragma acc wait

    // Print results
    for (i = 0; i < N; i++) {
        printf("a[%d] = %d, b[%d] = %d, c[%d] = %d\n", i, a[i], i, b[i], i, c[i]);
    }

    return 0;
}