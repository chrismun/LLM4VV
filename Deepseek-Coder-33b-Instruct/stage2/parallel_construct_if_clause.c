#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int data[N], i, sum = 0;
    int expected_sum = 0;

    // Initialize the array
    for (i = 0; i < N; i++) {
        data[i] = i;
        expected_sum += i;
    }

    // Compute the sum in parallel
    #pragma acc parallel loop copyin(data[0:N]) copy(sum)
    for (i = 0; i < N; i++) {
        sum += data[i];
    }

    // Check the result
    if (sum != expected_sum) {
        printf("Error: sum is %d, expected %d\n", sum, expected_sum);
        return 1;
    }

    printf("Success: sum is %d\n", sum);
    return 0;
}