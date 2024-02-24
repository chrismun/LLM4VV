#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 100;
    int *a = (int*)malloc(n * sizeof(int));

    #pragma acc data copyin(a[0:n])
    {
        // Do some computations with a

        #pragma acc free(a)
    }

    return 0;
}