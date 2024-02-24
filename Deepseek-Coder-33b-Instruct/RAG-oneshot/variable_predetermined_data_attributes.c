#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i, j;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize arrays
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // OpenACC region
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Parallelize the loop
        #pragma acc parallel loop
        for(i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    // Verify the results
    for(i = 0; i < N; i++) {
        if(b[i] != a[i]) {
            printf("Error: b[%d] = %d, expected %d\n", i, b[i], a[i]);
            return 1;
        }
    }

    printf("Verification successful\n");
    return 0;
}