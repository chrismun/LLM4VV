#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int *a, *b;
    int i;

    // Allocate memory for arrays a and b
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));

    // Initialize array a
    for (i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy data from array a to array b using OpenACC
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels present(a[0:N])
        {
            #pragma acc loop
            for (i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    // Verify the results
    for (i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Test passed.\n");
    return 0;
}