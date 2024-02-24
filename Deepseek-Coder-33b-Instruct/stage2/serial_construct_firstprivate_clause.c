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

    // Use OpenACC to sum the array
    #pragma acc parallel loop copy(sum) firstprivate(data)
    for (i = 0; i < N; i++) {
        sum += data[i];
    }

    printf("Sum: %d\n", sum);

    return 0;
}