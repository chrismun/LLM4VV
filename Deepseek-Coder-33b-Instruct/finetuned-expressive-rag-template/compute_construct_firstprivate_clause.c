#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], i, sum = 0;
    srand(time(NULL));

    // Initialize the array with random integers
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Compute the sum of the array in parallel using OpenACC
    #pragma acc parallel loop firstprivate(a) reduction(+:sum)
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    // Check the result
    int expected_sum = 0;
    for (i = 0; i < N; i++) {
        expected_sum += a[i];
    }

    if (sum == expected_sum) {
        printf("Test passed!\n");
        return 0;
    } else {
        printf("Test failed!\n");
        return 1;
    }
}