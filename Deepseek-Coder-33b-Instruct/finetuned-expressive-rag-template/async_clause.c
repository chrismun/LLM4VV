#include <stdlib.h>
#include <openacc.h>

int main() {
    int n = 1000;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    #pragma acc parallel loop async(1)
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }

    #pragma acc parallel loop async(1)
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }

    free(a);
    free(b);

    return 0;
}