pp
#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main() {
    int i;
    float a[N], b[N], c[N], d[N];

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N]) vector_length(8)
    {
        #pragma acc loop
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Check the result
    for (i = 0; i < N; i++) {
        d[i] = i + i;
        if (c[i] != d[i]) {
            printf("ERROR: c[%d] expected %f, but got %f\n", i, d[i], c[i]);
            return 1;
        }
    }

    printf("SUCCESS\n");
    return 0;
}