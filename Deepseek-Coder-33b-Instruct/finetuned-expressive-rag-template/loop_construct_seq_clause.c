#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], i, sum = 0;
    int sum_expected = 0;

    // Initialize the array
    for (i = 0; i < N; i++) {
        a[i] = i;
        sum_expected += a[i];
    }

    // Compute the sum of the array using OpenACC
    #pragma acc parallel loop seq
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    // Check if the sum is correct
    if (sum != sum_expected) {
        printf("Error: sum is not correct\n");
        return 1;
    }

    printf("Success: sum is correct\n");
    return 0;
}