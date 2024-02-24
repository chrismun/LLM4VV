#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], i, sum = 0;
    srand(0);

    // Initialize array
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Compute sum of array using OpenACC
    #pragma acc parallel loop firstprivate(a)
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("Sum: %d\n", sum);

    return 0;
}