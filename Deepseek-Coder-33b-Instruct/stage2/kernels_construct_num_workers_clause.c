#include <stdio.h>
#include <openacc.h>

int main() {
    int i;
    int n = 100;
    int a[n], b[n], c[n];

    for (i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc kernels num_workers(4)
    {
        for (i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }

    for (i = 0; i < n; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}