#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    #pragma acc data copyin(a[0:n]) create(b[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            b[i] = a[i];
        }

        #pragma acc attach(b)
        {
            // The data region b is attached to the device
            // The device can now access the data region b
            // The data region b is detached at the end of this block
        }
    }

    free(a);
    free(b);

    return 0;
}