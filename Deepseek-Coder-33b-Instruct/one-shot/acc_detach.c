#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < N; i++) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (b[i] != a[i]) {
            printf("Error at index %d\n", i);
            return 1;
        }
    }

    printf("Success!\n");
    return 0;
}