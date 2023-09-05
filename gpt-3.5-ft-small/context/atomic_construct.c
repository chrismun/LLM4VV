#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the size of the array
#define N 100

int main() {
    int i;
    int sum = 0;
    int a[N];

    // Initialize the array with random values
    srand(time(NULL));
    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Calculate the sum of the array using the atomic construct
    #pragma acc parallel loop present(a)
    #pragma acc atomic
    for (i = 0; i < N; i++) {
        sum += a[i];
    }

    // Check if the sum is correct
    int expected_sum = 0;
    for (i = 0; i < N; i++) {
        expected_sum += a[i];
    }
    if (sum != expected_sum) {
        printf("Sum calculation incorrect\n");
        return 1;
    }

    printf("Sum: %d\n", sum);

    return 0;