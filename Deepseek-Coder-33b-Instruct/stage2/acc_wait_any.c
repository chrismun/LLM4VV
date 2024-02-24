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
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels present(a[0:N], b[0:N], c[0:N]) async(1)
        for(int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc wait(1)

        int err = acc_wait_any(1, &c[0]);
        if (err != 0) {
            printf("Error: acc_wait_any returned %d\n", err);
            return 1;
        }
    }

    free(a);
    free(b);
    free(c);

    return 0;
}