#include <stdlib.h>
#include <openacc.h>

int main() {
    int N = 1000;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    #pragma acc parallel loop async(1)
    for (int i = 0; i < N; i++) {
        a[i] = b[i];
    }

    #pragma acc wait

    free(a);
    free(b);

    return 0;
}