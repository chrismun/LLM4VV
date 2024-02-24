#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                c[i] = a[i] + b[i];
            }
        }

        #pragma acc update self(b[0:N]) async(2)
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i] - b[i];
            }
        }

        #pragma acc wait(1, 2)
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", c[i]);
    }

    free(a);
    free(b);
    free(c);

    return 0;
}