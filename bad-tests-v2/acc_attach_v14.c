#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1024

int main() {
    int *a, *b;
    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));

    // Initialize the host array
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Attach the device array to the host array
    #pragma acc attach copyin(a[0:N])
    {
        #pragma acc kernels
        {
            // Copy the device array to the host array
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check if the device array is correctly attached to the host array
    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}