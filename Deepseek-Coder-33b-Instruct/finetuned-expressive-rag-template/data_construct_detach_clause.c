#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(a[0:N], b[0:N])
    {
        // Detach data construct
        #pragma acc data detach(a, b)
        {
            // Perform computations on device
            #pragma acc parallel loop
            for(int i = 0; i < N; i++) {
                a[i] += b[i];
            }
        }

        // Copy data back to host
        #pragma acc update host(a[0:N])
    }

    // Verify results
    for(int i = 0; i < N; i++) {
        if(a[i] != 2 * i) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Success\n");
    return 0;
}