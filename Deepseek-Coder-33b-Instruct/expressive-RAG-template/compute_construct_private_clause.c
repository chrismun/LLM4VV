#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <openacc.h>

#define N 100

int main() {
    int data[N];
    int sum = 0;
    int i;

    srand(time(NULL));

    // Initialize the array with random numbers
    for (i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    // Compute the sum of the array in parallel
    #pragma acc parallel copy(data) copy(sum)
    {
        #pragma acc loop reduction(+:sum) private(data)
        for (i = 0; i < N; i++) {
            sum += data[i];
        }
    }

    // Print the sum
    printf("Sum: %d\n", sum);

    return 0;
}