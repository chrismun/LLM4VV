#include <stdio.h>
#include <openacc.h>

int main() {
    int N = 1000000;
    int a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc kernels present(a[0:N], b[0:N], c[0:N]) async(1)
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc wait
        printf("All kernels have finished execution.\n");
    }

    return 0;
}