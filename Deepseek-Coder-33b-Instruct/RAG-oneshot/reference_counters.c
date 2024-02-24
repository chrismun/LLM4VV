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

    // Copy data to the device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Execute the kernel on the device
        #pragma acc kernels
        {
            // Copy data from the device to the host
            #pragma acc loop
            for(i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Verify the results
    for(i = 0; i < N; i++) {
        if(b[i] != a[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Success!\n");
    return 0;
}