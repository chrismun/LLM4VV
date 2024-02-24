#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int i;
    int sum = 0;
    int *a = (int*)malloc(N * sizeof(int));

    for(i = 0; i < N; i++) {
        a[i] = i + 1;
    }

    #pragma acc data copy(a[0:N])
    {
        #pragma acc parallel loop reduction(+:sum)
        for(i = 0; i < N; i++) {
            sum += a[i];
        }
    }

    printf("Sum: %d\n", sum);

    free(a);

    return 0;
}