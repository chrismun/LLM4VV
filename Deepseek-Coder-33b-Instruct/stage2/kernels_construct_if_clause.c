#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define ARRAY_SIZE 1000000
#define THRESHOLD 10000

int main() {
    int *array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    int sum = 0;

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    // Use OpenACC to parallelize the loop
    #pragma acc kernels copyin(array[0:ARRAY_SIZE]) copyout(sum) if (ARRAY_SIZE > THRESHOLD)
    {
        sum = 0;
        for (int i = 0; i < ARRAY_SIZE; i++) {
            sum += array[i];
        }
    }

    // Check the result
    if (sum != (ARRAY_SIZE * (ARRAY_SIZE - 1)) / 2) {
        printf("Test failed: sum is %d, expected %d\n", sum, (ARRAY_SIZE * (ARRAY_SIZE - 1)) / 2);
        return 1;
    }

    printf("Test passed\n");
    return 0;
}