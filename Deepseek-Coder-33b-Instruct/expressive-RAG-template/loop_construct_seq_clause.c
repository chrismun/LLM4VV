#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int data[N];
    int sum = 0;
    int i;

    // Initialize the array
    for (i = 0; i < N; i++) {
        data[i] = i;
    }

    // Compute the sum of the array using OpenACC
    #pragma acc parallel loop seq
    for (i = 0; i < N; i++) {
        sum += data[i];
    }

    // Check the result
    int expected_sum = N * (N - 1) / 2;
    if (sum == expected_sum) {
        printf("Test passed!\n");
        return 0;
    } else {
        printf("Test failed!\n");
        return 1;
    }
}