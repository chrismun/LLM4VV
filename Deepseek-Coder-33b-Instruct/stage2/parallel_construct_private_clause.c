#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

int main() {
    int data[N], sum = 0;
    int i, err = 0;

    // Initialize data array with random numbers
    for (i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    // Compute sum of array in parallel using OpenACC
    #pragma acc parallel private(sum)
    {
        sum = 0;
        #pragma acc loop reduction(+:sum)
        for (i = 0; i < N; i++) {
            sum += data[i];
        }
    }

    // Check if sum is correct
    int expected_sum = 0;
    for (i = 0; i < N; i++) {
        expected_sum += data[i];
    }

    if (sum != expected_sum) {
        err = 1;
        printf("Error: sum is %d, expected %d\n", sum, expected_sum);
    }

    return err;
}