#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int sum = 0;

    // Initialize array
    for(int i = 0; i < N; i++) {
        a[i] = i + 1;
    }

    // Perform reduction
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("Sum: %d\n", sum);

    free(a);

    return 0;
}