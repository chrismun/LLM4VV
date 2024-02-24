#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000000

int main() {
    int *a, *b;
    int i, err = 0;
    long sum = 0;

    a = (int*)malloc(N * sizeof(int));
    b = (int*)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(sum)
    {
        #pragma acc parallel loop reduction(+:sum)
        for (i = 0; i < N; i++) {
            sum += a[i] + b[i];
        }
    }

    printf("Sum: %ld\n", sum);

    free(a);
    free(b);

    return err;
}