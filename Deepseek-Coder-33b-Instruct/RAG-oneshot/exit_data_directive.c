#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize array a
    for(int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy data to device and back to host
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            for(int i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Verify the results
    for(int i = 0; i < N; i++) {
        if(a[i] != b[i]) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");
    return 0;
}