#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int i;
    int *a, *b, *c;

    // Allocate memory for vectors a, b, and c
    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));
    c = (int*)malloc(N * sizeof(int));

    // Initialize vectors a and b
    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // Perform vector addition using OpenACC
    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop vector
        for(i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Verify the results
    for(i = 0; i < N; i++) {
        if(c[i] != 2*i) {
            printf("Verification failed at index %d\n", i);
            return 1;
        }
    }

    printf("Verification passed\n");

    // Free memory
    free(a);
    free(b);
    free(c);

    return 0;
}