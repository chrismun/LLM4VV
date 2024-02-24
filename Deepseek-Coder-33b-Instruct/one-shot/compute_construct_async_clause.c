#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int *a = (int*)malloc(SIZE * sizeof(int));
    int *b = (int*)malloc(SIZE * sizeof(int));
    int sum = 0, product = 1;

    // Initialize the arrays
    for(int i = 0; i < SIZE; i++) {
        a[i] = i + 1;
        b[i] = i + 1;
    }

    // Compute the sum and product of the arrays in parallel
    #pragma acc parallel async(1) copyin(a[0:SIZE]) copy(sum)
    {
        #pragma acc loop reduction(+:sum)
        for(int i = 0; i < SIZE; i++) {
            sum += a[i];
        }
    }

    #pragma acc parallel async(2) copyin(b[0:SIZE]) copy(product)
    {
        #pragma acc loop reduction(*:product)
        for(int i = 0; i < SIZE; i++) {
            product *= b[i];
        }
    }

    // Wait for the tasks to complete
    #pragma acc wait

    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);

    free(a);
    free(b);

    return 0;
}