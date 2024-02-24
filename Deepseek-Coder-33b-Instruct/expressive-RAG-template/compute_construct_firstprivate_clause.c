#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], i, sum = 0;
    int sum_acc = 0;

    // Initialize array with random numbers
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Compute sum of array in serial
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    // Compute sum of array in parallel using OpenACC
    #pragma acc parallel loop copyin(a[:N]) firstprivate(sum_acc)
    for (i = 0; i < N; i++) {
        sum_acc += a[i];
    }

    // Check if the results are the same
    if (sum == sum_acc) {
        printf("Test passed!\n");
        return 0;
    } else {
        printf("Test failed!\n");
        return 1;
    }
}