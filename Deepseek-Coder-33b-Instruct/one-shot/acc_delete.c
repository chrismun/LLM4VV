#include <stdlib.h>
#include <openacc.h>

int main() {
    const int n = 100;
    int *a = (int*)malloc(n * sizeof(int));

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels
        for (int i = 0; i < n; i++) {
            a[i] = i;
        }

        #pragma acc exit data delete(a[0:n])
    }

    return 0;
}