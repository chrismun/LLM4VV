#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a, *b, *c;
    int i;

    // Allocate memory on the host
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));
    c = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Create device pointers
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        // Perform addition on the device
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
            }
        }
    }

    // Verify the results
    for(i = 0; i < N; i++) {
        if(c[i] != a[i] + b[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification successful\n");

    // Free memory
    free(a);
    free(b);
    free(c);

    return 0;
}