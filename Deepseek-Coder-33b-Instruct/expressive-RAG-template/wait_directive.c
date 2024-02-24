#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc wait

        // Check the results
        for(int i = 0; i < N; i++) {
            if(c[i] != 2*i) {
                printf("Error at index %d: expected %d, got %d\n", i, 2*i, c[i]);
                return 1; // Return non-zero to indicate an error
            }
        }
    }

    free(a);
    free(b);
    free(c);

    return 0; // Return zero to indicate success
}