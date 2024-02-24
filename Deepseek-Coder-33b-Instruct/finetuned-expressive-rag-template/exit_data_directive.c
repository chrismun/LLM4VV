#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], b[N];
    int i;

    // Initialize the arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy the data to the device
    #pragma acc data copyin(a) copyout(b)
    {
        // Enter data directive
        #pragma acc enter data copyin(a)

        // Perform the computation
        #pragma acc parallel loop
        for (i = 0; i < N; i++) {
            b[i] = a[i] * 2;
        }

        // Exit data directive
        #pragma acc exit data copyout(b)
    }

    // Check the results
    for (i = 0; i < N; i++) {
        if (b[i] != i * 2) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}