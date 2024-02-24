#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a, *b;
    int i;

    // Allocate memory on the host
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));

    // Initialize the arrays
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Copy data from host to device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Copy data from device to device
        #pragma acc memcpy device(b[0:N]) device(a[0:N])
        {
            // Perform computation on the device
            #pragma acc parallel loop
            for(i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Check the results
    for(i = 0; i < N; i++) {
        if(b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Success!\n");

    // Free the memory
    free(a);
    free(b);

    return 0;
}