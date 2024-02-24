#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    #pragma acc create(a[0:n], b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int i = 0; i < n; i++) {
                a[i] = i;
                b[i] = i * 2;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
    }

    free(a);
    free(b);

    return 0;
}