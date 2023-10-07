#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int i;
    int *a, *b, *c;

    a = (int*) malloc(N * sizeof(int));
    b = (int*) malloc(N * sizeof(int));
    c = (int*) malloc(N * sizeof(int));

    for(i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 2 * i;
        c[i] = 0;
    }

    #pragma acc data copy(a[0:N], b[0:N], c[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for(i = 0; i < N; i++) {
                #pragma acc atomic update
                c[i] = a[i] + b[i];
            }
        }
    }

    for(i = 0; i < N; i++) {
        if(c[i] != a[i] + b[i]) {
            printf("Test failed: c[%d] = %d, expected %d\n", i, c[i], a[i] + b[i]);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}