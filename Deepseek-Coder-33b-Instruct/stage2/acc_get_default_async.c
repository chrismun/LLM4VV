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

    #pragma acc parallel loop async(1)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Wait for the asynchronous task to complete
    #pragma acc wait

    // Check the results
    for (i = 0; i < N; i++) {
        if (c[i] != i + i) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}