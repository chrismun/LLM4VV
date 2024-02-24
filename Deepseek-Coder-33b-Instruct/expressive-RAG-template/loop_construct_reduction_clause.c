#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int data[SIZE];
    int sum = 0;
    int i;

    // Initialize the array
    for(i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    // Perform the reduction
    #pragma acc parallel loop reduction(+:sum)
    for(i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    // Print the result
    printf("Sum: %d\n", sum);

    return 0;
}