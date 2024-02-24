#include <stdio.h>
#include <omp.h>

#define N 1000

int main() {
    int a[N], b[N];
    int i;

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Attach arrays to device
    #pragma omp target data map(to:a) map(from:b)
    {
        // Use arrays on device
        #pragma omp target teams distribute parallel for
        for (i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }
    }

    // Check results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i] * 2) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}