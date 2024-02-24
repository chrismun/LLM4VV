#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int a[N], sum = 0;

    // Initialize array with random numbers
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Use OpenACC to sum the array in parallel
    #pragma acc parallel loop firstprivate(sum)
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }

    // Print the sum
    printf("Sum: %d\n", sum);

    return 0;
}