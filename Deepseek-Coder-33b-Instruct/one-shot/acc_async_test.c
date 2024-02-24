#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    int i;
    int sum = 0, product = 1;
    int *data = (int*)malloc(SIZE * sizeof(int));

    // Initialize data
    for(i = 0; i < SIZE; i++) {
        data[i] = i + 1;
    }

    // Compute sum and product in parallel
    #pragma acc parallel async(1) copy(data[0:SIZE])
    {
        #pragma acc loop reduction(+:sum)
        for(i = 0; i < SIZE; i++) {
            sum += data[i];
        }
    }

    #pragma acc parallel async(2) copy(data[0:SIZE])
    {
        #pragma acc loop reduction(*:product)
        for(i = 0; i < SIZE; i++) {
            product *= data[i];
        }
    }

    // Wait for both tasks to complete
    #pragma acc wait

    printf("Sum: %d\n", sum);
    printf("Product: %d\n", product);

    free(data);

    return 0;
}