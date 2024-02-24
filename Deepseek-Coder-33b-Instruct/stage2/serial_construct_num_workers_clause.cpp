#include <stdlib.h>
#include <openacc.h>

#define N 1000

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc parallel num_workers(4) copy(a[0:N], b[0:N])
    {
        #pragma acc loop worker
        for (int i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            printf("Test failed at index %d\n", i);
            return 1;
        }
    }

    printf("Test passed\n");
    return 0;
}