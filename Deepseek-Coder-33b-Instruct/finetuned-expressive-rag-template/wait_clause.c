#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels
        for (int i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc wait

        // The following code will not be executed until the kernels above have completed
        // This is where you would typically perform some operation that depends on the results of the kernels
    }

    free(a);
    free(b);
    free(c);

    return 0;
}